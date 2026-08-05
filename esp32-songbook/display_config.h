#pragma once

// CrowPanel ESP32 2.13" e-paper HMI display wiring, based on the local
// vendor example sketches in `crowpanel-esp32-docs/`.

constexpr int PIN_EPD_SCK = 12;
constexpr int PIN_EPD_MOSI = 11;
constexpr int PIN_EPD_RES = 10;
constexpr int PIN_EPD_DC = 13;
constexpr int PIN_EPD_CS = 14;
constexpr int PIN_EPD_BUSY = 9;
constexpr int PIN_PANEL_POWER = 7;

constexpr int PIN_BUTTON_HOME = 2;
constexpr int PIN_BUTTON_BACK = 1;
constexpr int PIN_NAV_NEXT = 4;
constexpr int PIN_NAV_PREV = 6;
constexpr int PIN_NAV_OK = 5;

constexpr bool INPUT_ACTIVE_HIGH = false;
constexpr bool USE_INTERNAL_PULLUPS = false;

// Logical screen orientation for the songbook UI: landscape, 250x122.
constexpr int SCREEN_WIDTH = 250;
constexpr int SCREEN_HEIGHT = 122;

constexpr int SCREEN_MARGIN_X = 4;
constexpr int SCREEN_MARGIN_Y = 4;
constexpr int TITLE_LINE_HEIGHT = 9;
constexpr int META_LINE_HEIGHT = 8;
constexpr int BODY_LINE_HEIGHT = 8;
constexpr int SECTION_GAP = 3;

constexpr int TITLE_CHARS_PER_LINE = 34;
constexpr int META_CHARS_PER_LINE = 40;
constexpr int BODY_CHARS_PER_LINE = 40;
