# ESP32 Songbook Prototype

This folder contains a first-pass local prototype for moving your exported songbook onto an ESP32 e-paper display.

The workflow is:

1. Put exported song JSON into `songbook-renderer/songs/`.
2. Run `python3 esp32-songbook/generate_song_data.py`.
3. Compile and upload `esp32-songbook/` with `arduino-cli` or the Arduino IDE.

## What gets stored on the device

The generator keeps only the compact data that is useful on a small display:

- `title`
- `artist`
- `capo`
- `tuning`
- `key`
- section labels such as `Intro`, `Verse`, `Pre-Chorus`, `Chorus`, `Bridge`
- each section's compact chord progression

It intentionally drops full lyric lines, chord column positioning, and the full raw tab text.

## Files

- `generate_song_data.py`: converts exported JSON into `generated/song_data.h`
- `esp32-songbook.ino`: renders songs on the e-paper display
- `display_config.h`: local pin and layout settings for the CrowPanel board
- `epd_driver.h` / `epd_driver.cpp`: local SSD1680-style e-paper driver adapted from the vendor examples
- `tiny_font.h`: small built-in bitmap font used by the prototype
- `generated/song_data.h`: auto-generated compact song library

## Generator usage

Default input:

```bash
python3 esp32-songbook/generate_song_data.py
```

Custom input/output:

```bash
python3 esp32-songbook/generate_song_data.py \
  --input-dir /path/to/song-json \
  --output /path/to/song_data.h \
  --max-sections 12 \
  --max-chords 48
```

## Arduino-side assumptions

This sketch is set up for the CrowPanel 2.13-inch board using the local vendor pinout you saved in `crowpanel-esp32-docs/info.txt`.

Current board mapping in [display_config.h](/Users/tomkaufmann/guitar-songs-offline/esp32-songbook/display_config.h:1):

- panel SPI/control: `SCK=12`, `MOSI=11`, `RES=10`, `DC=13`, `CS=14`, `BUSY=9`, panel power `7`
- buttons: `HOME=2`, `BACK/EXIT=1`
- navigation switch: `NEXT=4`, `PREV=6`, `OK=5`

The current navigation model is:

- `NEXT`: next song
- `PREV`: previous song
- `OK`: next page within the current song
- `BACK`: previous page
- `HOME`: jump to the first song

If you leave the hardware input pins at `-1`, the prototype still works over USB serial:

- `n`: next song
- `p`: previous song
- `]`: next page
- `[`: previous page
- `h`: first song
- `r`: redraw

## `arduino-cli` flow

There is now a small wrapper script:

```bash
chmod +x esp32-songbook/build.sh
esp32-songbook/build.sh
PORT=YOUR_PORT esp32-songbook/build.sh
```

Equivalent raw commands:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3 esp32-songbook
arduino-cli upload -p YOUR_PORT --fqbn esp32:esp32:esp32s3 esp32-songbook
```

Verified in this environment on August 5, 2026:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3 esp32-songbook
```

That compile succeeded. No third-party display library is required; the prototype uses the local driver files in this folder.

## Likely next improvements

- move the compact song library into LittleFS or SD instead of compiling it into flash
- add a small home screen with song index and navigation hints
- remember the last viewed song/page across resets
- add song search by first letter or artist
- add optional transpose support using the existing extractor logic
