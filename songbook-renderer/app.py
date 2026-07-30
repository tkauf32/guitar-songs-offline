from __future__ import annotations

import json
import re
from pathlib import Path
from flask import Flask, jsonify, render_template, send_from_directory

APP_DIR = Path(__file__).resolve().parent
SONGS_DIR = APP_DIR / "songs"

app = Flask(__name__, template_folder="templates", static_folder="static")


def slug(value: str) -> str:
    value = value.lower().strip()
    value = re.sub(r"[^a-z0-9]+", "-", value)
    return value.strip("-") or "song"


def load_songs():
    songs = []

    for path in sorted(SONGS_DIR.glob("*.json")):
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
            data["_filename"] = path.name
            data["_id"] = slug(f"{data.get('artist', '')}-{data.get('title', path.stem)}")
            songs.append(data)
        except Exception as exc:
            print(f"Skipping {path.name}: {exc}")

    return songs


@app.get("/")
def index():
    return render_template("index.html")


@app.get("/api/songs")
def list_songs():
    songs = load_songs()
    return jsonify([
        {
            "id": song["_id"],
            "filename": song["_filename"],
            "title": song.get("title", "Untitled"),
            "artist": song.get("artist", ""),
            "metadata": song.get("metadata", {}),
        }
        for song in songs
    ])


@app.get("/api/songs/<song_id>")
def get_song(song_id: str):
    for song in load_songs():
        if song["_id"] == song_id:
            return jsonify(song)
    return jsonify({"error": "Song not found"}), 404


@app.get("/songs/<path:filename>")
def raw_song(filename: str):
    return send_from_directory(SONGS_DIR, filename)


if __name__ == "__main__":
    SONGS_DIR.mkdir(exist_ok=True)
    app.run(host="0.0.0.0", port=5050, debug=True)
