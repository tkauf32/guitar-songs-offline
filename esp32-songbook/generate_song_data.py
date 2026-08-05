#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_INPUT_DIR = REPO_ROOT / "songbook-renderer" / "songs"
DEFAULT_OUTPUT = REPO_ROOT / "esp32-songbook" / "generated" / "song_data.h"


def slug(value: str) -> str:
    return re.sub(r"[^a-z0-9]+", "-", value.lower()).strip("-") or "song"


def parse_capo(value: object) -> int:
    if value is None:
        return -1

    match = re.search(r"-?\d+", str(value))
    return int(match.group(0)) if match else -1


def sanitize_text(value: object) -> str:
    text = str(value or "")
    text = text.replace("\r", " ").replace("\n", " ")
    text = re.sub(r"\s+", " ", text).strip()
    return text


def cpp_string(value: str) -> str:
    escaped = (
        value.replace("\\", "\\\\")
        .replace('"', '\\"')
        .replace("\t", " ")
        .replace("\n", " ")
    )
    return f'"{escaped}"'


def compact_progression(chords: list[object], max_chords: int) -> str:
    cleaned = [sanitize_text(chord) for chord in chords]
    cleaned = [chord for chord in cleaned if chord]
    if max_chords > 0:
        cleaned = cleaned[:max_chords]
    return "  ".join(cleaned)


def compact_song(data: dict, max_sections: int, max_chords: int) -> dict:
    title = sanitize_text(data.get("title")) or "Untitled"
    artist = sanitize_text(data.get("artist")) or "Unknown Artist"
    metadata = data.get("metadata") or {}

    sections = []
    for raw_section in data.get("sections") or []:
        label = sanitize_text(raw_section.get("label")) or "Section"
        progression = compact_progression(raw_section.get("progression") or [], max_chords)
        if progression:
            sections.append({"label": label, "progression": progression})
        if max_sections > 0 and len(sections) >= max_sections:
            break

    return {
        "id": slug(f"{artist}-{title}"),
        "title": title,
        "artist": artist,
        "capo": parse_capo(metadata.get("capo")),
        "tuning": sanitize_text(metadata.get("tuning")),
        "key": sanitize_text(metadata.get("key")),
        "sections": sections,
    }


def load_song_files(input_dir: Path) -> list[tuple[Path, dict]]:
    songs = []
    for path in sorted(input_dir.glob("*.json")):
        try:
            songs.append((path, json.loads(path.read_text(encoding="utf-8"))))
        except Exception as exc:
            print(f"Skipping {path.name}: {exc}")
    return songs


def render_header(compact_songs: list[dict]) -> str:
    lines: list[str] = []
    lines.append("#pragma once")
    lines.append("")
    lines.append("#include <stdint.h>")
    lines.append("")
    lines.append("struct SectionData {")
    lines.append("  const char* label;")
    lines.append("  const char* progression;")
    lines.append("};")
    lines.append("")
    lines.append("struct SongData {")
    lines.append("  const char* id;")
    lines.append("  const char* title;")
    lines.append("  const char* artist;")
    lines.append("  int16_t capo;")
    lines.append("  const char* tuning;")
    lines.append("  const char* key;")
    lines.append("  const SectionData* sections;")
    lines.append("  uint16_t section_count;")
    lines.append("};")
    lines.append("")

    for index, song in enumerate(compact_songs):
        lines.append(f"static const SectionData SONG_{index}_SECTIONS[] = {{")
        for section in song["sections"]:
            lines.append(
                f"  {{{cpp_string(section['label'])}, {cpp_string(section['progression'])}}},"
            )
        lines.append("};")
        lines.append("")

    if compact_songs:
        lines.append("static const SongData SONG_LIBRARY[] = {")
        for index, song in enumerate(compact_songs):
            lines.append("  {")
            lines.append(f"    {cpp_string(song['id'])},")
            lines.append(f"    {cpp_string(song['title'])},")
            lines.append(f"    {cpp_string(song['artist'])},")
            lines.append(f"    {song['capo']},")
            lines.append(f"    {cpp_string(song['tuning'])},")
            lines.append(f"    {cpp_string(song['key'])},")
            lines.append(f"    SONG_{index}_SECTIONS,")
            lines.append(f"    {len(song['sections'])}")
            lines.append("  },")
        lines.append("};")
    else:
        lines.append("static const SongData SONG_LIBRARY[1] = {};")
    lines.append("")
    lines.append(f"static const uint16_t SONG_LIBRARY_COUNT = {len(compact_songs)};")
    lines.append("")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Generate a compact ESP32 song library header from exported song JSON."
    )
    parser.add_argument(
        "--input-dir",
        type=Path,
        default=DEFAULT_INPUT_DIR,
        help=f"Directory containing exported song JSON files. Default: {DEFAULT_INPUT_DIR}",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=DEFAULT_OUTPUT,
        help=f"Header path to generate. Default: {DEFAULT_OUTPUT}",
    )
    parser.add_argument(
        "--max-sections",
        type=int,
        default=12,
        help="Maximum number of non-empty sections to keep per song.",
    )
    parser.add_argument(
        "--max-chords",
        type=int,
        default=48,
        help="Maximum number of chord tokens to keep per section progression.",
    )
    args = parser.parse_args()

    input_dir = args.input_dir.resolve()
    output = args.output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)

    if not input_dir.exists():
        print(f"Input directory does not exist: {input_dir}")
        compact_songs: list[dict] = []
    else:
        compact_songs = [
            compact_song(song, args.max_sections, args.max_chords)
            for _, song in load_song_files(input_dir)
        ]

    header = render_header(compact_songs)
    output.write_text(header, encoding="utf-8")
    print(f"Wrote {len(compact_songs)} compact song(s) to {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
