const SHARPS = ["C","C#","D","D#","E","F","F#","G","G#","A","A#","B"];
const FLATS  = ["C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"];

let songs = [];
let currentSong = null;
let transpose = 0;

const songList = document.querySelector("#songList");
const content = document.querySelector("#content");
const title = document.querySelector("#title");
const meta = document.querySelector("#meta");
const transposeLabel = document.querySelector("#transposeLabel");
const viewMode = document.querySelector("#viewMode");
const search = document.querySelector("#search");

function noteIndex(note) {
  const sharp = SHARPS.indexOf(note);
  return sharp >= 0 ? sharp : FLATS.indexOf(note);
}

function transposeChord(chord, semitones, preferFlats = false) {
  return chord.split("/").map(part => {
    const match = part.match(/^([A-G])([#b]?)(.*)$/);
    if (!match) return part;

    const [, letter, accidental, suffix] = match;
    const index = noteIndex(letter + accidental);
    if (index < 0) return part;

    const scale = preferFlats ? FLATS : SHARPS;
    const target = ((index + semitones) % 12 + 12) % 12;
    return scale[target] + suffix;
  }).join("/");
}

function transposeTextLine(line, semitones) {
  if (!line?.chords?.length) return line?.text || "";

  let chars = [...line.text];
  const replacements = line.chords
    .map(token => ({
      start: token.column,
      original: token.chord,
      next: transposeChord(token.chord, semitones)
    }))
    .sort((a, b) => b.start - a.start);

  for (const item of replacements) {
    chars.splice(item.start, item.original.length, ...item.next);
  }

  return chars.join("");
}

async function loadSongs() {
  songs = await fetch("/api/songs").then(r => r.json());
  renderSongList();

  if (songs.length) {
    openSong(songs[0].id);
  }
}

function renderSongList() {
  const query = search.value.trim().toLowerCase();
  songList.innerHTML = "";

  for (const song of songs.filter(song =>
    `${song.title} ${song.artist}`.toLowerCase().includes(query)
  )) {
    const button = document.createElement("button");
    button.className = "song-item";
    button.dataset.id = song.id;
    button.innerHTML = `
      <div class="song-title">${escapeHTML(song.title)}</div>
      <div class="song-artist">${escapeHTML(song.artist || "")}</div>
    `;
    button.addEventListener("click", () => openSong(song.id));
    songList.appendChild(button);
  }
}

async function openSong(id) {
  currentSong = await fetch(`/api/songs/${id}`).then(r => r.json());
  transpose = 0;
  updateActiveSong();
  render();
}

function updateActiveSong() {
  document.querySelectorAll(".song-item").forEach(el => {
    el.classList.toggle("active", el.dataset.id === currentSong?._id);
  });
}

function render() {
  if (!currentSong) return;

  title.textContent = currentSong.title || "Untitled";

  const md = currentSong.metadata || {};
  meta.textContent = [
    currentSong.artist,
    md.key ? `Key ${md.key}` : "",
    md.capo ? `Capo ${md.capo}` : "",
    md.tuning ? `Tuning ${md.tuning}` : ""
  ].filter(Boolean).join(" · ");

  transposeLabel.textContent = transpose > 0 ? `+${transpose}` : `${transpose}`;

  if (viewMode.value === "raw") {
    content.className = "content";
    content.innerHTML = `<pre class="raw">${escapeHTML(currentSong.rawTab || "")}</pre>`;
    return;
  }

  const sections = currentSong.sections || [];
  content.className = "content";
  content.innerHTML = sections.map(section => {
    if (viewMode.value === "compact") {
      const chords = (section.progression || [])
        .map(chord => transposeChord(chord, transpose))
        .join("  ");

      return `
        <article class="section">
          <h2>${escapeHTML(section.label || section.id || "Section")}</h2>
          <div class="progression">${escapeHTML(chords || "—")}</div>
        </article>
      `;
    }

    const lines = (section.lines || []).map(line => {
      const className = line.type === "chords" ? "line chord-line" : "line";
      const text = line.type === "chords"
        ? transposeTextLine(line, transpose)
        : line.text || "";

      return `<div class="${className}">${escapeHTML(text) || "&nbsp;"}</div>`;
    }).join("");

    return `
      <article class="section">
        <h2>${escapeHTML(section.label || section.id || "Section")}</h2>
        ${lines}
      </article>
    `;
  }).join("");
}

function escapeHTML(value) {
  return String(value ?? "")
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;");
}

document.querySelector("#minus").addEventListener("click", () => {
  transpose--;
  render();
});

document.querySelector("#plus").addEventListener("click", () => {
  transpose++;
  render();
});

document.querySelector("#reset").addEventListener("click", () => {
  transpose = 0;
  render();
});

viewMode.addEventListener("change", render);
search.addEventListener("input", renderSongList);

loadSongs();
