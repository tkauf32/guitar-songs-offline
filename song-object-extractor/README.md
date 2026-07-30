# Song Object Extractor v0.5

Version 0.2 is a tiny unpacked Chrome extension that saves the chord sheet currently visible in your browser as structured JSON.

## Install

1. Open `chrome://extensions`.
2. Turn on **Developer mode**.
3. Click **Load unpacked**.
4. Select this folder.
5. Open a supported chord page whose tab is visible.
6. Click the extension toolbar icon.

The song is saved under your Downloads folder:

`Downloads/Songbook/artist--song-title.json`

## What the JSON preserves

- Title, artist, source URL, key, capo, tuning and difficulty
- Every labeled section: intro, verse, pre-chorus, chorus, bridge, etc.
- Original chord and lyric lines
- Each chord's character-column position for chord-over-word rendering
- A compact chord progression for each section
- The untouched extracted tab text

Example line:

```json
{
  "type": "chords",
  "text": "B                        E",
  "chords": [
    {"chord": "B", "column": 0},
    {"chord": "E", "column": 25}
  ]
}
```

This lets a renderer either:

- display only `section.progression` on a small screen, or
- reconstruct chord-over-lyric positioning from `line.chords[].column`.

## Transposition

`transpose.js` contains reusable functions for:

- major/minor/extended chords
- sharps and flats
- slash chords such as `D/F#`
- positive or negative semitone movement

Example:

```js
import { transposeSong } from "./transpose.js";

const inA = transposeSong(song, 5, false);
```

Capo and transposition should be modeled separately:

- `written key`: the chord shapes shown
- `capo`: fret number
- `sounding key`: written key shifted upward by capo semitones
- `display transpose`: user-selected chord-shape shift

## Deliberate limitation

This extension extracts text already rendered and visible in your own browser session. It does not bypass authentication, subscription restrictions, or inaccessible content.

## Next useful layer

A local library app can scan all JSON files and expose:

- `/songs`
- `/songs/:id`
- `/songs/:id?transpose=-2`
- `/songs/:id/compact`

That output can be served to a Raspberry Pi or e-ink device over the local network.


## Version 0.2

Adds fallbacks for older/outlier pages that use plain section headings or begin directly with chord lines instead of bracketed labels.


## Debug behavior

When extraction fails, v0.3 automatically downloads a file named:

`Downloads/Songbook/debug-<timestamp>.json`

That file contains the visible page text and the highest-scoring tab container. It does not contain cookies or passwords. The debug file can be used to add support for an unusual page format.


## v0.4 fix

Uses a data URL for downloads because Manifest V3 service workers do not provide `URL.createObjectURL()`.

## v0.5

- One toolbar click immediately extracts and downloads the current song JSON.
- Added a custom music-note-inside-download-arrow Chrome toolbar icon.
- No popup or second confirmation is used by the extension.

For true one-click saving, Chrome's **Ask where to save each file before downloading** setting must be turned off.
