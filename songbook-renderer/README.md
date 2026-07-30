# Songbook Renderer

A tiny local web app for the JSON files created by Song Object Extractor.

## Start on macOS

1. Put exported `.json` song files into the `songs` folder.
2. Double-click `run.command`.
3. Open:

   `http://localhost:5050`

The first run creates a local Python environment and installs Flask.

## Features

- Local song library
- Search by title or artist
- Compact section progressions
- Lyrics with chord positioning
- Raw tab view
- Transpose up or down by semitone
- Slash-chord support
- Print-friendly layout

## Folder structure

```text
songbook-renderer/
├── app.py
├── run.command
├── requirements.txt
├── songs/
├── static/
└── templates/
```

## E-ink use

Open the site from another device on the same network using the computer's local IP:

`http://YOUR-COMPUTER-IP:5050`

The compact view is intentionally minimal and works well on small monochrome displays.

## Notes

The renderer uses the structured `sections`, `progression`, `lines`, and chord `column` values in the exported JSON. It does not fetch any tabs itself.
