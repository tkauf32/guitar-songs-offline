# Guitar Songs Offline

Two small local tools for building and browsing a personal song library.

## What is here

- `song-object-extractor/`: unpacked Chrome extension that saves the visible chord sheet in the current tab as structured JSON
- `songbook-renderer/`: tiny Flask app that reads those JSON files and serves a local browser-based songbook

## Quick start

1. Load `song-object-extractor/` as an unpacked extension in Chrome.
2. Use it on a supported chord page to download song JSON files.
3. Create `songbook-renderer/songs/` and put the exported `.json` files there.
4. Run `songbook-renderer/run.command`.
5. Open `http://localhost:5050`.

## Notes

- This repo does not include local archives, virtual environments, or exported song files.
- The renderer installs its Python dependency on first run.

See the README in each subfolder for project-specific details.
