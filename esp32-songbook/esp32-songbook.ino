#include <Arduino.h>

#include "display_config.h"
#include "epd_driver.h"
#include "generated/song_data.h"
#include "tiny_font.h"

namespace {

enum class ScreenMode {
  Index,
  Song,
  Jump,
};

struct SectionSpan {
  uint16_t start;
  uint16_t end;
};

uint8_t frameBuffer[EPD_BUFFER_SIZE];
ScreenMode currentScreen = ScreenMode::Index;
uint16_t currentSongIndex = 0;
uint16_t currentPageIndex = 0;
uint16_t indexTopSong = 0;
char jumpLetter = 'A';
bool needsRedraw = true;

bool isInputPressed(int pin) {
  if (pin < 0) {
    return false;
  }

  const int level = digitalRead(pin);
  return INPUT_ACTIVE_HIGH ? level == HIGH : level == LOW;
}

void configureInputPin(int pin) {
  if (pin < 0) {
    return;
  }

  pinMode(pin, USE_INTERNAL_PULLUPS ? INPUT_PULLUP : INPUT);
}

void clearFrameBuffer() {
  memset(frameBuffer, 0x00, sizeof(frameBuffer));
}

void drawPixel(int x, int y, bool black) {
  if (!black || x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
    return;
  }

  // Match the vendor draw-point transform for USE_HORIZONTIAL == 2 so the
  // logical UI stays landscape while the raw panel memory remains SSD1680-native.
  const int xPoint = y;
  const int yPoint = SCREEN_WIDTH - x - 1;
  const int bytesPerColumn = (SCREEN_HEIGHT + 7) / 8;
  const int index = (xPoint / 8) + (yPoint * bytesPerColumn);
  frameBuffer[index] |= static_cast<uint8_t>(0x80 >> (xPoint % 8));
}

const uint8_t* glyphFor(char c) {
  if (c >= 'a' && c <= 'z') {
    c = static_cast<char>(c - 'a' + 'A');
  }

  return lookupGlyph(c);
}

void drawChar(int x, int y, char c) {
  const uint8_t* glyph = glyphFor(c);
  for (int col = 0; col < FONT_WIDTH; col++) {
    const uint8_t bits = glyph[col];
    for (int row = 0; row < FONT_HEIGHT; row++) {
      if (bits & (1 << row)) {
        drawPixel(x + col, y + row, true);
      }
    }
  }
}

void drawText(int x, int y, const String& text) {
  int cursorX = x;
  for (size_t i = 0; i < text.length(); i++) {
    drawChar(cursorX, y, text[i]);
    cursorX += FONT_ADVANCE;
  }
}

void drawHorizontalLine(int x1, int x2, int y) {
  if (x2 < x1) {
    const int tmp = x1;
    x1 = x2;
    x2 = tmp;
  }
  for (int x = x1; x <= x2; x++) {
    drawPixel(x, y, true);
  }
}

void drawVerticalLine(int x, int y1, int y2) {
  if (y2 < y1) {
    const int tmp = y1;
    y1 = y2;
    y2 = tmp;
  }
  for (int y = y1; y <= y2; y++) {
    drawPixel(x, y, true);
  }
}

void drawRect(int x, int y, int w, int h) {
  if (w <= 1 || h <= 1) {
    return;
  }
  drawHorizontalLine(x, x + w - 1, y);
  drawHorizontalLine(x, x + w - 1, y + h - 1);
  drawVerticalLine(x, y, y + h - 1);
  drawVerticalLine(x + w - 1, y, y + h - 1);
}

void fillRect(int x, int y, int w, int h) {
  for (int yy = y; yy < y + h; yy++) {
    drawHorizontalLine(x, x + w - 1, yy);
  }
}

String trimText(const String& value) {
  int start = 0;
  while (start < value.length() && value[start] == ' ') {
    start++;
  }

  int end = value.length();
  while (end > start && value[end - 1] == ' ') {
    end--;
  }

  return value.substring(start, end);
}

String normalizeSpaces(const String& value) {
  String out;
  bool lastWasSpace = false;
  for (size_t i = 0; i < value.length(); i++) {
    char c = value[i];
    if (c == '\r' || c == '\n' || c == '\t') {
      c = ' ';
    }
    if (c == ' ') {
      if (!lastWasSpace) {
        out += c;
      }
      lastWasSpace = true;
    } else {
      out += c;
      lastWasSpace = false;
    }
  }
  return trimText(out);
}

int wrapText(const String& text, int charsPerLine, String* lines, int maxLines) {
  if (charsPerLine <= 0) {
    return 0;
  }

  String normalized = normalizeSpaces(text);
  if (!normalized.length()) {
    if (lines && maxLines > 0) {
      lines[0] = "";
    }
    return 1;
  }

  int lineCount = 0;
  String line;
  int start = 0;

  while (start < normalized.length()) {
    while (start < normalized.length() && normalized[start] == ' ') {
      start++;
    }
    int end = normalized.indexOf(' ', start);
    if (end < 0) {
      end = normalized.length();
    }

    String token = normalized.substring(start, end);
    if (token.length() > charsPerLine) {
      if (line.length()) {
        if (lines && lineCount < maxLines) {
          lines[lineCount] = line;
        }
        lineCount++;
        line = "";
      }

      int tokenStart = 0;
      while (tokenStart < token.length()) {
        String chunk = token.substring(tokenStart, tokenStart + charsPerLine);
        if (lines && lineCount < maxLines) {
          lines[lineCount] = chunk;
        }
        lineCount++;
        tokenStart += charsPerLine;
      }
    } else {
      String candidate = line.length() ? line + " " + token : token;
      if (candidate.length() > charsPerLine && line.length()) {
        if (lines && lineCount < maxLines) {
          lines[lineCount] = line;
        }
        lineCount++;
        line = token;
      } else {
        line = candidate;
      }
    }

    start = end + 1;
  }

  if (line.length() || lineCount == 0) {
    if (lines && lineCount < maxLines) {
      lines[lineCount] = line;
    }
    lineCount++;
  }

  return lineCount;
}

void drawWrappedText(int x, int& y, const String& text, int charsPerLine, int lineHeight) {
  String lines[32];
  const int count = wrapText(text, charsPerLine, lines, 32);
  for (int i = 0; i < count; i++) {
    drawText(x, y, lines[i]);
    y += lineHeight;
  }
}

String truncateText(const String& text, int maxChars) {
  if (maxChars <= 0 || text.length() <= maxChars) {
    return text;
  }
  if (maxChars <= 3) {
    return text.substring(0, maxChars);
  }
  return text.substring(0, maxChars - 3) + "...";
}

int songsPerIndexPage() {
  return 10;
}

char songInitial(uint16_t songIndex) {
  if (songIndex >= SONG_LIBRARY_COUNT) {
    return '#';
  }

  const char* title = SONG_LIBRARY[songIndex].title;
  if (!title || !title[0]) {
    return '#';
  }

  for (int i = 0; title[i]; i++) {
    char c = title[i];
    if (c >= 'a' && c <= 'z') {
      c = static_cast<char>(c - 'a' + 'A');
    }
    if (c >= 'A' && c <= 'Z') {
      return c;
    }
    if (c >= '0' && c <= '9') {
      return '#';
    }
  }

  return '#';
}

uint16_t firstSongForLetter(char letter) {
  if (!SONG_LIBRARY_COUNT) {
    return 0;
  }

  const char target = (letter >= 'a' && letter <= 'z')
      ? static_cast<char>(letter - 'a' + 'A')
      : letter;

  for (uint16_t i = 0; i < SONG_LIBRARY_COUNT; i++) {
    if (songInitial(i) == target) {
      return i;
    }
  }

  return currentSongIndex;
}

bool letterExists(char letter) {
  if (!SONG_LIBRARY_COUNT) {
    return false;
  }
  for (uint16_t i = 0; i < SONG_LIBRARY_COUNT; i++) {
    if (songInitial(i) == letter) {
      return true;
    }
  }
  return false;
}

void advanceJumpLetter(int delta) {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }

  char candidate = jumpLetter;
  for (int i = 0; i < 27; i++) {
    if (candidate == '#') {
      candidate = delta > 0 ? 'A' : 'Z';
    } else {
      candidate = static_cast<char>(candidate + delta);
      if (candidate > 'Z') {
        candidate = '#';
      } else if (candidate < 'A') {
        candidate = '#';
      }
    }

    if (letterExists(candidate)) {
      jumpLetter = candidate;
      needsRedraw = true;
      return;
    }
  }
}

void clampIndexWindow() {
  if (!SONG_LIBRARY_COUNT) {
    indexTopSong = 0;
    currentSongIndex = 0;
    return;
  }

  if (currentSongIndex >= SONG_LIBRARY_COUNT) {
    currentSongIndex = SONG_LIBRARY_COUNT - 1;
  }

  const int visible = songsPerIndexPage();
  if (currentSongIndex < indexTopSong) {
    indexTopSong = currentSongIndex;
  } else if (currentSongIndex >= indexTopSong + visible) {
    indexTopSong = currentSongIndex - visible + 1;
  }
}

String metaLine(const SongData& song) {
  String meta = "CAPO ";
  meta += song.capo >= 0 ? String(song.capo) : String("-");

  if (song.tuning && song.tuning[0]) {
    meta += "  TUNING ";
    meta += song.tuning;
  }

  if (song.key && song.key[0]) {
    meta += "  KEY ";
    meta += song.key;
  }

  return meta;
}

int sectionHeight(const SectionData& section) {
  const int progressionLines = wrapText(String(section.progression), BODY_CHARS_PER_LINE, nullptr, 0);
  return BODY_LINE_HEIGHT + progressionLines * BODY_LINE_HEIGHT + SECTION_GAP;
}

int pageTopY() {
  return SCREEN_MARGIN_Y + (TITLE_LINE_HEIGHT * 2) + META_LINE_HEIGHT + 5;
}

int pageBottomY() {
  return SCREEN_HEIGHT - SCREEN_MARGIN_Y;
}

int pageCountForSong(const SongData& song) {
  if (song.section_count == 0) {
    return 1;
  }

  int pageCount = 1;
  int y = pageTopY();
  for (uint16_t i = 0; i < song.section_count; i++) {
    const int nextHeight = sectionHeight(song.sections[i]);
    if (y + nextHeight > pageBottomY() && y > pageTopY()) {
      pageCount++;
      y = pageTopY();
    }
    y += nextHeight;
  }

  return pageCount;
}

SectionSpan spanForPage(const SongData& song, uint16_t pageIndex) {
  if (song.section_count == 0) {
    return {0, 0};
  }

  uint16_t currentPage = 0;
  uint16_t start = 0;
  int y = pageTopY();

  for (uint16_t i = 0; i < song.section_count; i++) {
    const int nextHeight = sectionHeight(song.sections[i]);
    if (y + nextHeight > pageBottomY() && y > pageTopY()) {
      if (currentPage == pageIndex) {
        return {start, i};
      }
      currentPage++;
      start = i;
      y = pageTopY();
    }
    y += nextHeight;
  }

  if (currentPage == pageIndex) {
    return {start, song.section_count};
  }

  return {0, song.section_count};
}

void clampPageIndex() {
  if (SONG_LIBRARY_COUNT == 0) {
    currentPageIndex = 0;
    return;
  }

  const int totalPages = pageCountForSong(SONG_LIBRARY[currentSongIndex]);
  if (currentPageIndex >= totalPages) {
    currentPageIndex = totalPages - 1;
  }
}

void nextSong() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  currentSongIndex = (currentSongIndex + 1) % SONG_LIBRARY_COUNT;
  clampIndexWindow();
  needsRedraw = true;
}

void prevSong() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  currentSongIndex = currentSongIndex == 0 ? SONG_LIBRARY_COUNT - 1 : currentSongIndex - 1;
  clampIndexWindow();
  needsRedraw = true;
}

void nextPage() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  const int totalPages = pageCountForSong(SONG_LIBRARY[currentSongIndex]);
  currentPageIndex = (currentPageIndex + 1) % totalPages;
  needsRedraw = true;
}

void prevPage() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  const int totalPages = pageCountForSong(SONG_LIBRARY[currentSongIndex]);
  currentPageIndex = currentPageIndex == 0 ? totalPages - 1 : currentPageIndex - 1;
  needsRedraw = true;
}

void firstSong() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  currentSongIndex = 0;
  currentPageIndex = 0;
  indexTopSong = 0;
  needsRedraw = true;
}

void openCurrentSong() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  currentScreen = ScreenMode::Song;
  currentPageIndex = 0;
  needsRedraw = true;
}

void openIndexScreen() {
  currentScreen = ScreenMode::Index;
  clampIndexWindow();
  needsRedraw = true;
}

void openJumpScreen() {
  currentScreen = ScreenMode::Jump;
  jumpLetter = songInitial(currentSongIndex);
  if (!letterExists(jumpLetter)) {
    jumpLetter = letterExists('A') ? 'A' : '#';
  }
  needsRedraw = true;
}

void acceptJumpSelection() {
  if (!SONG_LIBRARY_COUNT) {
    return;
  }
  currentSongIndex = firstSongForLetter(jumpLetter);
  clampIndexWindow();
  currentScreen = ScreenMode::Index;
  needsRedraw = true;
}

void drawIndexScreen() {
  clearFrameBuffer();

  int y = SCREEN_MARGIN_Y;
  drawText(SCREEN_MARGIN_X, y, "SONGBOOK");
  y += TITLE_LINE_HEIGHT;

  const String countLabel = String(SONG_LIBRARY_COUNT) + " SONGS";
  drawText(SCREEN_MARGIN_X, y, countLabel);
  y += META_LINE_HEIGHT + 2;

  if (!SONG_LIBRARY_COUNT) {
    drawText(SCREEN_MARGIN_X, y, "NO SONGS FOUND");
    y += BODY_LINE_HEIGHT;
    drawText(SCREEN_MARGIN_X, y, "RUN GENERATE_SONG_DATA.PY");
    epdDisplayImage(frameBuffer);
    return;
  }

  clampIndexWindow();

  const int visible = songsPerIndexPage();
  for (int row = 0; row < visible; row++) {
    const uint16_t songIndex = indexTopSong + row;
    if (songIndex >= SONG_LIBRARY_COUNT) {
      break;
    }

    const bool selected = songIndex == currentSongIndex;
    const int rowY = y - 1;
    if (selected) {
      drawRect(0, rowY, SCREEN_WIDTH, BODY_LINE_HEIGHT + 2);
      fillRect(2, rowY + 2, 4, BODY_LINE_HEIGHT - 2);
    }

    const String marker = selected ? ">" : " ";
    const String title = truncateText(String(SONG_LIBRARY[songIndex].title), 24);
    const String artist = truncateText(String(SONG_LIBRARY[songIndex].artist), 13);
    String line = marker + String(songIndex + 1) + ". " + title;
    if (artist.length()) {
      line += " - " + artist;
    }

    drawText(SCREEN_MARGIN_X, y, truncateText(line, 40));
    y += BODY_LINE_HEIGHT;
  }

  drawText(SCREEN_MARGIN_X, SCREEN_HEIGHT - BODY_LINE_HEIGHT, "OK OPEN  HOLD OK JUMP  HOME");
  epdDisplayImage(frameBuffer);
}

void drawJumpScreen() {
  clearFrameBuffer();

  int y = SCREEN_MARGIN_Y;
  drawText(SCREEN_MARGIN_X, y, "A-Z JUMP");
  y += TITLE_LINE_HEIGHT + 2;

  String line = "LETTER ";
  line += jumpLetter;
  drawText(SCREEN_MARGIN_X, y, line);
  y += BODY_LINE_HEIGHT + 3;

  const uint16_t previewIndex = firstSongForLetter(jumpLetter);
  if (SONG_LIBRARY_COUNT && previewIndex < SONG_LIBRARY_COUNT) {
    drawText(SCREEN_MARGIN_X, y, truncateText(String(SONG_LIBRARY[previewIndex].title), 32));
    y += BODY_LINE_HEIGHT;
    drawText(SCREEN_MARGIN_X, y, truncateText(String(SONG_LIBRARY[previewIndex].artist), 24));
    y += BODY_LINE_HEIGHT + 4;
  }

  drawText(SCREEN_MARGIN_X, y, "PREV/NEXT CHANGE");
  y += BODY_LINE_HEIGHT;
  drawText(SCREEN_MARGIN_X, y, "OK SELECT");
  y += BODY_LINE_HEIGHT;
  drawText(SCREEN_MARGIN_X, y, "HOME/BACK CANCEL");
  epdDisplayImage(frameBuffer);
}

void drawSongPage() {
  clearFrameBuffer();

  if (SONG_LIBRARY_COUNT == 0) {
    int y = SCREEN_MARGIN_Y;
    drawText(SCREEN_MARGIN_X, y, "NO SONGS FOUND");
    y += BODY_LINE_HEIGHT;
    drawText(SCREEN_MARGIN_X, y, "RUN GENERATE_SONG_DATA.PY");
    epdDisplayImage(frameBuffer);
    return;
  }

  const SongData& song = SONG_LIBRARY[currentSongIndex];
  const int totalPages = pageCountForSong(song);
  const SectionSpan span = spanForPage(song, currentPageIndex);

  int y = SCREEN_MARGIN_Y;
  drawWrappedText(SCREEN_MARGIN_X, y, truncateText(String(song.title), TITLE_CHARS_PER_LINE * 2), TITLE_CHARS_PER_LINE, TITLE_LINE_HEIGHT);
  drawWrappedText(SCREEN_MARGIN_X, y, truncateText(String(song.artist), TITLE_CHARS_PER_LINE), TITLE_CHARS_PER_LINE, TITLE_LINE_HEIGHT);
  drawWrappedText(SCREEN_MARGIN_X, y, truncateText(metaLine(song), META_CHARS_PER_LINE), META_CHARS_PER_LINE, META_LINE_HEIGHT);

  const String pageLabel = String(currentSongIndex + 1) + "/" + String(SONG_LIBRARY_COUNT) +
      " P" + String(currentPageIndex + 1) + "/" + String(totalPages);
  const int pageLabelX = SCREEN_WIDTH - SCREEN_MARGIN_X - pageLabel.length() * FONT_ADVANCE;
  drawText(pageLabelX < 150 ? 150 : pageLabelX, SCREEN_MARGIN_Y, pageLabel);

  y = pageTopY();
  for (uint16_t i = span.start; i < span.end; i++) {
    drawText(SCREEN_MARGIN_X, y, truncateText(String(song.sections[i].label) + ":", 14));
    y += BODY_LINE_HEIGHT;
    drawWrappedText(SCREEN_MARGIN_X + 8, y, String(song.sections[i].progression), BODY_CHARS_PER_LINE - 1, BODY_LINE_HEIGHT);
    y += SECTION_GAP;
  }

  epdDisplayImage(frameBuffer);
}

void readSerialCommands() {
  while (Serial.available()) {
    const char command = static_cast<char>(Serial.read());
    if (command == 'n') {
      nextSong();
    } else if (command == 'p') {
      prevSong();
    } else if (command == ']') {
      nextPage();
    } else if (command == '[') {
      prevPage();
    } else if (command == 'h') {
      firstSong();
      openIndexScreen();
    } else if (command == 'o') {
      openCurrentSong();
    } else if (command == 'i') {
      openIndexScreen();
    } else if (command == 'j') {
      openJumpScreen();
    } else if (command == 'r') {
      needsRedraw = true;
    }
  }
}

void readPanelInputs() {
  static bool homeWasPressed = false;
  static bool backWasPressed = false;
  static bool nextWasPressed = false;
  static bool prevWasPressed = false;
  static bool okWasPressed = false;
  static unsigned long okPressedAt = 0;

  const bool homePressed = isInputPressed(PIN_BUTTON_HOME);
  const bool backPressed = isInputPressed(PIN_BUTTON_BACK);
  const bool nextPressed = isInputPressed(PIN_NAV_NEXT);
  const bool prevPressed = isInputPressed(PIN_NAV_PREV);
  const bool okPressed = isInputPressed(PIN_NAV_OK);

  if (homePressed && !homeWasPressed) {
    openIndexScreen();
    firstSong();
  }
  if (backPressed && !backWasPressed) {
    if (currentScreen == ScreenMode::Song || currentScreen == ScreenMode::Jump) {
      openIndexScreen();
    } else {
      currentSongIndex = indexTopSong;
      clampIndexWindow();
      needsRedraw = true;
    }
  }
  if (nextPressed && !nextWasPressed) {
    if (currentScreen == ScreenMode::Song) {
      nextPage();
    } else if (currentScreen == ScreenMode::Jump) {
      advanceJumpLetter(1);
    } else {
      nextSong();
    }
  }
  if (prevPressed && !prevWasPressed) {
    if (currentScreen == ScreenMode::Song) {
      prevPage();
    } else if (currentScreen == ScreenMode::Jump) {
      advanceJumpLetter(-1);
    } else {
      prevSong();
    }
  }
  if (okPressed && !okWasPressed) {
    okPressedAt = millis();
  }
  if (!okPressed && okWasPressed) {
    const unsigned long heldFor = millis() - okPressedAt;
    if (currentScreen == ScreenMode::Jump) {
      acceptJumpSelection();
    } else if (currentScreen == ScreenMode::Song) {
      openIndexScreen();
    } else if (heldFor >= 700) {
      openJumpScreen();
    } else {
      openCurrentSong();
    }
  }

  homeWasPressed = homePressed;
  backWasPressed = backPressed;
  nextWasPressed = nextPressed;
  prevWasPressed = prevPressed;
  okWasPressed = okPressed;
}

}  // namespace

void setup() {
  Serial.begin(115200);
  delay(50);

  pinMode(PIN_PANEL_POWER, OUTPUT);
  digitalWrite(PIN_PANEL_POWER, HIGH);

  configureInputPin(PIN_BUTTON_HOME);
  configureInputPin(PIN_BUTTON_BACK);
  configureInputPin(PIN_NAV_NEXT);
  configureInputPin(PIN_NAV_PREV);
  configureInputPin(PIN_NAV_OK);

  epdInit();
  clampIndexWindow();
  clampPageIndex();
  drawIndexScreen();
  epdSleep();
  needsRedraw = false;

  Serial.println("ESP32 Songbook ready.");
  Serial.println("Index: PREV/NEXT move, OK open, hold OK jump, HOME index-top");
  Serial.println("Jump: PREV/NEXT letter, OK select, HOME/BACK cancel");
  Serial.println("Song: PREV/NEXT page, OK index, HOME index");
  Serial.println("Serial: n/p move songs, o open, i index, j jump, ]/[ page, h home, r redraw");
}

void loop() {
  readSerialCommands();
  readPanelInputs();

  if (needsRedraw) {
    clampIndexWindow();
    clampPageIndex();
    epdInit();
    if (currentScreen == ScreenMode::Index) {
      drawIndexScreen();
    } else if (currentScreen == ScreenMode::Jump) {
      drawJumpScreen();
    } else {
      drawSongPage();
    }
    epdSleep();
    needsRedraw = false;
  }

  delay(20);
}
