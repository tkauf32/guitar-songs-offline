const SHARP_NOTES = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
const FLAT_NOTES  = ["C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"];

export function transposeChord(chord, semitones, preferFlats = false) {
  return chord
    .split("/")
    .map(part => transposeChordPart(part, semitones, preferFlats))
    .join("/");
}

function transposeChordPart(part, semitones, preferFlats) {
  const match = part.match(/^([A-G])([#b]?)(.*)$/);
  if (!match) return part;

  const [, letter, accidental, suffix] = match;
  const root = letter + accidental;
  const sourceIndex = noteIndex(root);
  if (sourceIndex < 0) return part;

  const notes = preferFlats ? FLAT_NOTES : SHARP_NOTES;
  const targetIndex = ((sourceIndex + semitones) % 12 + 12) % 12;
  return notes[targetIndex] + suffix;
}

function noteIndex(note) {
  const sharpIndex = SHARP_NOTES.indexOf(note);
  if (sharpIndex >= 0) return sharpIndex;
  return FLAT_NOTES.indexOf(note);
}

export function transposeSong(song, semitones, preferFlats = false) {
  return {
    ...song,
    metadata: {
      ...song.metadata,
      transposedBy: semitones
    },
    sections: song.sections.map(section => ({
      ...section,
      progression: section.progression.map(chord =>
        transposeChord(chord, semitones, preferFlats)
      ),
      lines: section.lines.map(line => ({
        ...line,
        chords: line.chords.map(token => ({
          ...token,
          chord: transposeChord(token.chord, semitones, preferFlats)
        }))
      }))
    }))
  };
}
