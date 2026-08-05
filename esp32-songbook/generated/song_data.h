#pragma once

#include <stdint.h>

struct SectionData {
  const char* label;
  const char* progression;
};

struct SongData {
  const char* id;
  const char* title;
  const char* artist;
  int16_t capo;
  const char* tuning;
  const char* key;
  const SectionData* sections;
  uint16_t section_count;
};

static const SectionData SONG_0_SECTIONS[] = {
  {"Intro", "Bb  Eb  Bb  Eb  Bb  Eb  Cm7  Eb  F"},
  {"Verse 1", "Bb  Eb  Bb  Eb  Bb  Eb  Cm7  Eb  Bb  Eb  Bb  Eb  Bb  Eb  Cm7  Eb"},
  {"Pre-Chorus 1", "Cm7  Fsus4  F  Eb"},
  {"Chorus 1", "Bb  Eb  Gm7  Eb  Bb  F  Eb  Bb  Eb  Gm7  Eb  Bb  F  Bb"},
  {"Post-Chorus 1", "Eb  Bb  Eb  Bb"},
  {"Verse 2", "Eb  Bb  Eb  Bb  Eb  Cm7  Eb  Cm7"},
  {"Pre-Chorus 2", "Fsus4  F  Eb  Bb"},
  {"Chorus 2", "Eb  Gm7  Eb  Bb  F  Eb  Bb  Eb  Gm7  Eb  Bb  F  Cm7  Cm  Eb"},
  {"Post-Chorus 2", "Bb  F/A  Cm7  Eb  Fsus4  F  Eb  Bb  Eb  Gm  Eb  Bb  F  Eb  Bb  Eb  Gm7  Eb  Bb  F"},
  {"Outro", "Bb  Eb  Bb  Eb  Bb  Eb  Bb"},
};

static const SectionData SONG_1_SECTIONS[] = {
  {"Intro - Piano Arranged for Guitar", "B  G  D  A  E  B  G  D  A  E"},
  {"Verse 1", "C  Am7  Em  Fmaj7  G  C  Am7  Em  Fmaj7  F  Fmaj7"},
  {"Chorus", "G  C  Am7  G  Em  Dm7  C  Fmaj7  G  C  Am7  G  Em  Dm7  C  Fmaj7  C  Am7  Em  Fmaj7"},
  {"Verse 2", "G  C  Am7  Em  Fmaj7  G  C  Am7  Em  Fmaj7  Fmaj7"},
  {"Chorus", "G  C  Am7  G  Em  Dm7  C  Fmaj7  C  Am7  G  Em  Dm7  C  Fmaj7  C  Am7  Em  Fmaj7"},
  {"Bridge", "C  Am7  Em  Fmaj7  Fmaj7"},
  {"Outro", "G  C  Am7  G  Em  Dm7  C  Fmaj7  C  Am7  G  Em  Dm7  C  Fmaj7  C  Am7  Em  Fmaj7"},
};

static const SectionData SONG_2_SECTIONS[] = {
  {"Intro", "Bm  G  D  A/C#  B  G  D  A  E  Bm  G  D  A  B  G  D  A  E"},
  {"Verse 1", "D  G  D  D  A  D  D  G  D  Bm  A  D"},
  {"Pre-chorus", "Bm  A  D  G  Bm  A  Bm  A  D  G  D  A"},
  {"Chorus", "G  A  Bm  D  A  G  G  A  Bm  D  A  G  G  A  Bm  D  A  G  G  A  Bm  D  A  G"},
  {"Instrumental", "G  A  Bm  D  D/F#  G"},
  {"Verse 2", "D  G  D  Bm  A  D  D  G  D  Bm  A  D"},
  {"Pre-chorus", "Bm  A  D  G  Bm  A  Bm  A  D  G  Bm  A"},
  {"Chorus", "G  A  Bm  D  A  G  G  A  Bm  D  A  G  G  A  Bm  D  A  G  G  A  Bm  D  A  G"},
  {"Outro", "G  A  Bm  D  D/F#  G"},
};

static const SectionData SONG_3_SECTIONS[] = {
  {"Intro", "C  G  Em  D"},
  {"Verse 1", "C  G  Em  D  C  G  Em  D"},
  {"Pre-Chorus", "C  G  Em  D  C  G  Em  D"},
  {"Chorus", "G  Em  D  C  G  Em  D  C  G  D  C  G  D"},
  {"Verse 2", "C  G  Em  D  C  G  Em  D"},
  {"Pre-Chorus", "C  G  Em  D  C  G  Em  D"},
  {"Chorus", "G  Em  D  C  G  Em  D  C  G  D  C  G  D"},
  {"Instrumental", "C  G  Em  D"},
  {"Bridge", "C  G  Em  D  C  G  Em  D"},
  {"Pre-Chorus", "C  G  Em  D  C  G  Em  D"},
  {"Chorus", "G  Em  D  C  G  Em  D  C  G  D  C  G  D  C  G  Em  D"},
  {"Outro", "C  G  Em  D"},
};

static const SectionData SONG_4_SECTIONS[] = {
  {"Intro", "A  Bm  D  A  A  D/A  A  G  E  A  B  G  D  A"},
  {"Verse", "A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  B  G  D  A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  B  G  D  A"},
  {"Chorus", "A  D/A  D/A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  Bm  D  Bm  A  D/A  D/A  A  A  B  G  D  E"},
  {"Verse", "A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  B  G  D  A  A  Bm  Bm  D  Bm  A  E"},
  {"Chorus", "D  A  D/A  D/A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  B  D  A  E  D  A"},
  {"Chorus", "A  A  D/A  A  Bm  Bm  D  Bm  A  D/A  D/A  A  A  Bm  Bm  D  Bm  A  D/A  D/A  A"},
  {"Outro", "A  A  D/A  A  Bm  D  Bm  A  D/A  D/A  A  A  A  D/A  A  Bm  D  Bm  A  B  G  D  A  E"},
};

static const SectionData SONG_5_SECTIONS[] = {
  {"Intro", "C#m  C#sus2  C#m  C#sus2  C#m"},
  {"Verse 1", "A  E  B  C#m  A  E  B  Badd9  B  A  E  B  C#m  A  E  B  Badd9  B"},
  {"Chorus", "C#m  E  A  B  C#5  A  E  A  E/G#  B  C#m"},
  {"Verse 2", "A  E  B  C#m  A  E  B  Badd9  B  A  E  B  C#m  A  E  B  Badd9  B"},
  {"Chorus", "C#m  E  A  B  C#5  A  E  A  E/G#  B  C#m  B  C#5  A  E  A  B  C#5  A  E  A  E"},
  {"Chorus", "B  C#5  A  E  A  B  C#5  A  E  A  B  C#5  A  E  A  B  C#5  A  E  A  E/G#  B  C#m  B  C#5  A  E  A  B  C#5  A  E  A  E  B  C#m"},
};

static const SectionData SONG_6_SECTIONS[] = {
  {"Intro", "D  Eb  Bb  Gb  Db  Db  D  D/F#  D"},
  {"Verse 1", "D  G  D  D  G  D  Am7  G  D  D  D/F#  D"},
  {"Verse 2", "D  G  D  Am7  G  D"},
  {"Chorus", "Bm  G  D  A  A#dim7  Bm  G  D  A  D  D"},
  {"Verse 3", "D  G  D  D  G  D  Am7  G  D"},
  {"Chorus", "Bm  G  D  A  A#dim7  Bm  G  D  A  D  D"},
  {"Verse 4", "D  G  D  D  D  D/F#  D  G  D  Am7  G  D"},
  {"Chorus", "Bm  G  D  A  A#dim7  Bm  D  A  Bm  G  A  D  D  D/F#  D  D"},
};

static const SectionData SONG_7_SECTIONS[] = {
  {"Intro", "G  D  Em  C  G  D  Em  C  G  D  C"},
  {"Verse 1", "G  D  Em  C  G  D  C  G  D  Em  C  G  D  C"},
  {"Chorus", "G  D  Em  C  G  D  C  G  D  Em  C  G  D  C"},
  {"Instrumental", "G  D  Em  C  G  D  C"},
  {"Verse 2", "G  D  Em  C  G  D  C  G  D  Em  C  G  D  C"},
  {"Chorus", "G  D  Em  C  G  D  C  G  D  Em  C  G  D  C"},
  {"Instrumental", "G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D"},
  {"Outro", "G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D  C  G  D  Em  C  G  D  C"},
};

static const SectionData SONG_8_SECTIONS[] = {
  {"Intro", "Am  E7  G  D  F  C  Dm  E7"},
  {"Verse", "Am  E7  G  D  F  C  Dm  E7  Am  E7  G  D  F  C  Dm  E7"},
  {"Chorus", "F  C  E7  Am  F  C  Dm  E7"},
  {"Verse", "Am  E7  G  D  F  C  Dm  E7  Am  E7  G  D  F  C  Dm  E7"},
  {"Chorus", "F  C  E7  Am  F  C  Dm  E7"},
  {"Verse", "Am  E7  G  D  F  C  Dm  E7  Am  E7  G  D  F  C  Dm  E7"},
  {"Outro Solo", "Am  E7  G  D  F  C  Dm  E7"},
  {"Harmonies", "Am  E7  G  D  F  C  Dm  E7"},
};

static const SectionData SONG_9_SECTIONS[] = {
  {"Intro", "Dm  C  Dm  F  C"},
  {"Verse 1", "Dm  C  Dm  C  F  G"},
  {"Chorus", "F  C  Dm  G  F  Am  F  G  C  Dm  C"},
  {"Verse 2", "Dm  C  Dm  C  F  G"},
  {"Chorus", "F  C  Dm  G  F  Am  F  G  C"},
  {"Bridge", "F  G  Am  G  F  G  Dm  G"},
  {"Chorus", "F  C  Dm  G  F  Am  F  G  Am  D  F  G  C"},
  {"Outro", "Dm  C  Dm  F  C"},
};

static const SectionData SONG_10_SECTIONS[] = {
  {"Verse 1", "Am7  Dm7  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Chorus", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7"},
  {"Instrumental", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Verse 2", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Chorus", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Chorus", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7"},
  {"Instrumental", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Verse 3", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Chorus", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E  Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
  {"Instrumental", "Am7  Dm7  G  G7  Cmaj7  Fmaj7  Bm7b5  Esus4  E"},
};

static const SectionData SONG_11_SECTIONS[] = {
  {"Chords", "A  Bm  Bm/A  Bsus2  G  F#m  Gmaj7"},
  {"Intro", "C#m  C#sus2  A  Amaj7  A"},
  {"Verse 1", "E  F#m  A  C#m  B  A  E  F#m  A  C#m  B  A"},
  {"Verse 2", "E  F#m  A  C#m  B  A  E  F#m  A  C#m  B  A"},
  {"Chorus", "C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A"},
  {"Interlude", "C#m  C#sus2  A  Amaj7  A"},
  {"Verse 3", "E  F#m  A  C#m  B  A  E  F#m  A  C#m  B  A"},
  {"Chorus", "C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A"},
  {"Instrumental", "C#m  C#m/B  E  E  C#m  C#m/B  A  A  C#m  C#m/B  E  E  C#m  C#m/B  A  A  C#m  C#sus2  A  A  C#m  C#sus2  A  A  C#m  C#sus2  A  A  C#m  C#sus2  A  G#m  A  C#m  A  G#m  C#m  C#m  A  G#m  C#m  C#m  C#m  C#m/B  A  A  C#m  C#m/B"},
  {"Chorus", "C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A  C#m  B  A"},
  {"Outro", "C#m  B  A  C#m  B  A  C#m  B  C#m"},
  {"Coda", "C#m  C#m/B  A  A  C#m  C#m/B  A  A  C#m  C#m/B  A  A  C#m  C#m/B  A  A"},
};

static const SectionData SONG_12_SECTIONS[] = {
  {"Verse 1", "C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G"},
  {"Chorus", "C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C"},
  {"Verse 2", "C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G"},
  {"Chorus", "C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C  Dm  Am  G  C"},
  {"Outro", "C  Dm  Am  G  C  Dm  Am  G  C"},
};

static const SectionData SONG_13_SECTIONS[] = {
  {"Verse 1", "C  G  Am  F  C  G  Am  F"},
  {"Pre-chorus 1", "C  G  Am  F  C  G  Am  F  C"},
  {"Chorus", "C  G  Am  F  C  G  Am  F  C"},
  {"Verse 2", "C  G  Am  F  C  G  Am  F"},
  {"Pre-chorus 2", "C  G  Am  F  C  G  Am  F  C"},
  {"Chorus", "C  G  Am  F  C  G  Am  F  C"},
  {"Bridge", "C  G  Am  F  C  G  Am  C"},
  {"Chorus", "C  G  Am  F  C  G  Am  F  C"},
};

static const SectionData SONG_14_SECTIONS[] = {
  {"Intro", "G  G/F#  Em7  Cadd9"},
  {"Verse 1", "G  G/F#  Em7  Cadd9  G  G/F#  Em7  Cadd9  G  G/F#  Em7  Cadd9  D/F#"},
  {"Chorus", "Cadd9  D/F#  G  Cadd9  D/F#  G  Cadd9  D/F#  G  D/F#  Em7  Cadd9  D/F#  Em7  Cadd9  D/F#  G  G/F#  Em7  Cadd9"},
  {"Verse 2", "G  G/F#  Em7  Cadd9  G  G/F#  Em7  Cadd9"},
  {"Chorus", "Cadd9  D/F#  G  Cadd9  D/F#  G  Cadd9  D/F#  G  D/F#  Em7  Cadd9  D/F#  Em7  Cadd9  D/F#  G"},
  {"Interlude", "Cadd9  Em7  Cadd9  Em7  Cadd9  Em7  D/F#  Cadd9  D/F#"},
  {"Outro", "Cadd9  D/F#  G  Cadd9  D/F#  G  Cadd9  D/F#  G  D/F#  Em7  Cadd9  D/F#  G  D/F#  Em7  Cadd9  D/F#  Em7  Cadd9  D/F#  G"},
};

static const SectionData SONG_15_SECTIONS[] = {
  {"Intro", "E  B  C#m  A  B  G  D  A  E  E  B  G#m  A  B  G  D  A  E"},
  {"Verse 1", "E  B  C#m  A  E  B  G#m  A  E  B  C#m  A  E  B  G#m  A  E  B  C#m  A  E  B  G#m  A  E  B  C#m  A  E  B  G#m  A"},
  {"Chorus", "A  E  A  E  A  E  A  B  E  B  E  A  E  B  C#m  A"},
  {"Verse 2", "E  B  C#m  A  E  B  G#m  A  E  B  C#m  A  E  B  G#m  A"},
  {"Chorus", "A  E  A  E  A  E  A  B  E  B  E  A  E  B  C#m  A  E  B  G#m  A"},
  {"Outro", "E  B  C#m  A  E  B  G#m  A  E  B  C#m  A  E  B  G#m  A  E  B  C#m  A  E  B  G#m  A"},
};

static const SectionData SONG_16_SECTIONS[] = {
  {"Intro", "C  Am  G  F"},
  {"Verse 1", "C  Am  F  C  C  Am  F  C  G"},
  {"Chorus 1", "F  Am  C  F  Am  C  F  Am  C  G  Dm  C  F"},
  {"Interlude", "C  Am  G  F"},
  {"Verse 2", "C  Am  F  C  C  Am  F  C  G"},
  {"Chorus 2", "F  Am  C  F  Am  C  F  Am  C  G  Dm  C  F"},
  {"Outro", "C  Am  G  F  C  Am  G  F  C  Am  G  F  C  Am  G  F  C  Am  G  F  C  Am  G  F"},
};

static const SectionData SONG_17_SECTIONS[] = {
  {"Song", "Am  Asus4  G  D  C  F  E  Em  Esus4  A  Dm  Dsus4  Am  Asus4  Am  G  D  D  C  C  Am  G  D  C  G  D  G  C  G  Am  Asus4  Am  G  D  D  Am  Asus4  Am  G  D  D  C  C  Am  G  D  Am  G"},
};

static const SectionData SONG_18_SECTIONS[] = {
  {"Solo", "G  Bb  C  G"},
};

static const SectionData SONG_19_SECTIONS[] = {
  {"Verse 1", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E"},
  {"Pre-Chorus", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E"},
  {"Chorus", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A"},
  {"Post-Chorus", "E  F#m  D  E"},
  {"Verse 2", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E"},
  {"Pre-Chorus", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E"},
  {"Chorus", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A"},
  {"Post Chorus", "E  F#m  D  E  F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E"},
  {"Outro", "F#m  D  A  E  F#m  D  E  F#m  D  A  E  F#m  D  E"},
};

static const SectionData SONG_20_SECTIONS[] = {
  {"Intro", "Am  G/B  C  F  C  G  Am  G/B  C  F  C  G"},
  {"Verse", "C  F  C  G2  C  F  C  G2"},
  {"Pre-Chorus", "Am  G/B  C  F  C  G  Am  G/B  C  F  C  G"},
  {"Chorus", "C  Em  G  C  Em  G"},
  {"Verse", "C  F  C  G2  C  F  C  G2"},
  {"Chorus", "C  Em  G  C  Em  G  C  Em  G  C  Em  G"},
  {"Verse", "C  F  C  G2  G  C  F  C  G2  G"},
  {"Pre-Chorus", "Am  G/B  C  F  C  G  Am  G/B  C  F  C  G"},
  {"Bridge", "C  G/B  Am  F  C  G  C  G/B  Am  F  C  G  C  G/B  Am  F  C  G"},
  {"Chorus", "C  Em  G  C  Em  G  C  Em  G  C  Em  G  C"},
};

static const SectionData SONG_21_SECTIONS[] = {
  {"Intro", "E  F#m  C#m  B"},
  {"Verse 1", "B  E  F#m  C#m  B  E  F#m  C#m  B  E  F#m  C#m  B"},
  {"Pre-chorus", "D  A  E  D  A  B"},
  {"Chorus", "E  F#m  C#m  B  E  F#m  C#m  B  B  E"},
  {"Verse 2", "F#m  C#m  B  E  F#m  C#m  B  E  F#m  C#m  B"},
  {"Pre-Chorus", "D  A  E  D  A  B"},
  {"Chorus", "E  F#m  C#m  B  E  F#m  C#m  B  E  F#m  C#m  B"},
};

static const SectionData SONG_22_SECTIONS[] = {
  {"Intro", "D  Em  G"},
  {"Verse 1", "D  Em  G  D  Em  G  D  Em  G  D  Em  G"},
  {"Pre-Chorus", "Bm  A  G  Bm  A  G"},
  {"Chorus", "D  Em  G  D  Em  G  D  Em  G  Bm  A  G  Bm  D  G"},
  {"Verse 2", "D  Em  G  D  Em  G  D  Em  G  D  Em  G"},
  {"Pre-Chorus", "Bm  A  G  Bm  A  G"},
  {"Chorus", "D  Em  G  D  Em  G  D  Em  G  Bm  A  G  Bm  D  G  Bm  A  G"},
  {"Interlude", "D  Em  G"},
  {"Outro", "Bm  A  G  Bm  D  G  Bm  A  G  Bm  D  G"},
};

static const SectionData SONG_23_SECTIONS[] = {
  {"Intro", "C  F  G  G  Em  F"},
  {"Verse 1", "C  F  G  Em  F  C  F  G  Em  F  C  F  G"},
  {"Chorus 1", "C  F  G  Em  F  C  F  G  Em  F"},
  {"Post-Chorus 1", "C  F  G  Em  F  C"},
  {"Verse 2", "F  G  C  F  G"},
  {"Chorus 2", "C  F  G  Em  F  C  F  G  Em  F"},
  {"Post-Chorus 2", "C  F  G  Em  F  C  F  G  Em  F"},
  {"Outro", "C  F  G  Em  F"},
};

static const SectionData SONG_24_SECTIONS[] = {
  {"Intro", "Am  F"},
  {"Verse 1", "Am  F  Am  F  G  Am  F  G  Am  F  Am  F  Am  F  F  G"},
  {"Chorus", "Am  F  F  G  Am  F  F  G  Am  F  F  G  Am  F  F"},
  {"Verse 2", "Am  F  G  Am  F  G  Am  F  Am  F  Am  F  F  G"},
  {"Chorus", "Am  F  F  G  Am  F  F  G  Am  F  F  G  Am  F  F  G  Am  F  F  G  Am  F"},
};

static const SectionData SONG_25_SECTIONS[] = {
  {"Intro", "E  F#m  Emaj7  F#m"},
  {"Verse 1", "E  F#m  Emaj7  F#m  E  F#m  A  Bm  Amaj7  Bm  E  F#m  Emaj7  A  Cmaj7  B  E  F#m  Emaj7  F#m"},
  {"Verse 2", "E  F#m  Emaj7  F#m  E  F#m  A  Bm  Amaj7  Bm  E  F#m  Emaj7  A  Cmaj7  B  E  F#m  Emaj7  F#m"},
  {"Chorus", "E  D  A  B  C#m  A  B  B7"},
  {"Verse 3", "E  F#m  Emaj7  F#m  E  F#m  A  Bm  Amaj7  Bm  E  F#m  Emaj7  A  Cmaj7  B  E  F#m  Cmaj7  B  E"},
  {"Outro", "E  F#m  Emaj7  F#m  E  F#m  Emaj7  F#m"},
};

static const SectionData SONG_26_SECTIONS[] = {
  {"Intro", "E  A  E  A  E  A  E  A"},
  {"Verse", "E  A  E  C#m  B  A  A  E  A  E  A  E  C#m  B  A  E"},
  {"Chorus", "C#m7  A  C#m7  A  C#m7  A  F#7  A"},
  {"Instrumental", "E  A  E  A"},
  {"Verse", "E  A  E  C#m  B  A  A  E  A  E  A  E  C#m  B  A  A  E"},
  {"Chorus", "C#m7  A  C#m7  A  C#m7  A  F#7  A"},
  {"Bridge", "E  D/E  A/E  E  E  D/E  A  A"},
  {"Chorus", "C#m7  A  C#m7  A  C#m7  A  F#7  A  C#m7  A  C#m7  A  C#m7  A  F#7  A  C#m7  A  C#m7  A  C#m7  A  F#7  A"},
};

static const SectionData SONG_27_SECTIONS[] = {
  {"Intro", "C  Am7  Gsus4  G  C  Am7  Gsus4  G"},
  {"Verse 1", "C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G"},
  {"Verse 2", "C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G"},
  {"Chorus", "F  C  G  G  F  C  G  G  F  C  G  E7  Am  F  G"},
  {"Verse 3", "C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G"},
  {"Chorus", "F  C  G  G  F  C  G  G  F  C  G  E7  Am  F  F  G  G"},
  {"Solo", "Am  G  F  C  Am  G  F  F  G  Gsus4"},
  {"Chorus", "G  F  C  G  G  F  C  G  G  Am  G  F  C  Am  G  F"},
  {"Outro", "C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G  C  Am7  Gsus4  G  C"},
};

static const SectionData SONG_28_SECTIONS[] = {
  {"Intro/Verse", "Bm  D/A  D  A  F#  D  A  D  D/F#  D  G  D  D  A  F#  D  A  D"},
  {"Chorus", "D  G(9)  D  D  G(9)  D  G(9)  D  A/D  D  A  F#  D  A  D  Bm7  G(9)  D  Bm7  G(9)  D  G(9)  D  A/D  D  A  F#  D  A  D"},
  {"Bridge/Verse", "Bm7  D  D  A  F#  D  A  D  D/F#  D  G  D  D  A  F#  D  A  D"},
};

static const SectionData SONG_29_SECTIONS[] = {
  {"Verse 1", "Em  G/B  C  D  G/B  C  Em  G/B  C  D  G/B  C  Em  G/B  C  D  G/B  C  Em  G/B  C  D  G/B  C"},
  {"Interlude", "C  D"},
  {"Chorus", "Em  D  G  C  Em  D  G  C  Em  D  G  C  Em  D  G  C"},
  {"Verse 2", "Em  G/B  C  D  G/B  C  Em  G/B  C  D  G/B  C  Em  G/B  C  D  G/B  C  Em  G/B  C  D  G/B  C"},
  {"Interlude", "C  D"},
  {"Chorus", "Em  D  G  C  Em  D  G  C  Em  D  G  C  Em  D  G  C"},
  {"Bridge", "C  D  Em  G  C  D  Em  G"},
  {"Interlude", "Em  D  G/B  C  Em  D  G/B  C"},
  {"Chorus", "Em  D  G  C  Em  D  G  C  Em  D  G  C  Em  D  G  C"},
  {"Outro", "Em  D  G  C  Em  D  G  C"},
};

static const SectionData SONG_30_SECTIONS[] = {
  {"Intro", "C  D/F#  G  Em  D  G"},
  {"Verse 1", "C  G  Em  D/F#  G  C  G  Em  D/F#  G  C  G  Em  D/F#  G  C  G  Em  D/F#  G  C  G  Em  D/F#  G  C  G  Em  D/F#  G"},
  {"Verse 2", "C  G  C  G  Em  D/F#  G  C  G  Em  D/F#  G  C  G  Em  D/F#  G"},
};

static const SectionData SONG_31_SECTIONS[] = {
  {"Intro", "C/G  G  F  C/G  G"},
  {"Verse 1", "C/G  G  F  C/G  G  C/G  G  F  C/G  G  C/G  G  F  C/G  G"},
  {"Break", "C/G  G  F  C/G  G"},
  {"Verse 2", "C/G  G  F  C/G  G  C/G  G  F  C/G  G  C/G  G  F  C/G  G"},
  {"Break", "C/G  G  F  C/G  G"},
  {"Verse 3", "C/G  G  F  C/G  G  C/G  G  F  C/G  G  C/G  G  F  C/G  G  C/G  G  F  C/G  G  C/G  G  F  C/G  G"},
  {"Outro", "C/G  G  F  C/G  G"},
};

static const SectionData SONG_32_SECTIONS[] = {
  {"Intro", "D  Bm  A  G  D"},
  {"Verse 1", "D  G  D  Bm  A  G  D  G  D  Bm  A  G  D  G  D  Bm  A  G  D  G  Bm  A  G"},
  {"Chorus", "Bm  A  G  D  D/C#  Bm  A  G  D  Bm  A  G  D  Bm  A  G  D  Bm  A  G  D"},
  {"Verse 2", "D  G  D  Bm  A  G  D  G  D  Bm  A  G"},
  {"Chorus", "Bm  A  G  D  D/C#  Bm  A  G  D  Bm  A  G  D  Bm  A  G  D  Bm  A  G  D  Bm  A  G  D"},
  {"Outro", "D  G  D  Bm  A  G"},
};

static const SectionData SONG_33_SECTIONS[] = {
  {"Intro", "Em7  A  D  G"},
  {"Chorus", "Em  A  D  G  Em  A  D  G  Em  A  D  G  Em  A  D  G"},
  {"Verse 1", "Em  A  D  G  Em  A  D  G"},
  {"Pre-Chorus", "Em  A  D  G  Em  A  D  G"},
  {"Chorus", "Em  A  D  G  Em  A  D  G  Em  A  D  G  Em  A  D  G"},
  {"Post-Chorus", "Em  A  D  G  Em  A  D  G"},
  {"Verse 2", "Em  A  D  G  Em  A  D  G"},
  {"Pre-Chorus", "Em  A  D  G  Em  A  D  G"},
  {"Chorus", "Em  A  D  G  Em  A  D  G  Em  A  D  G  Em  A  D  G"},
  {"Post-Chorus", "Em  A  D  G  Em  A  D  G  Em  A  D  G  Em  A  D  G"},
  {"Outro", "Em  A  D  G  Em  A  D  G  Em  A  D  G  Em  A  D  G"},
};

static const SectionData SONG_34_SECTIONS[] = {
  {"Verse 1", "Am  D  Em  Bm  C  Am  D  Em  Bm  C  G  Am  D  Em  Bm  C  Am  D  Em  Bm  C  G"},
  {"Chorus", "Em  Bm  C  Em  Bm  C  G"},
  {"Bridge", "Am  D  Em  Bm  C  Am  D  Em"},
  {"Instrumental", "Am  D  Em  Bm  C  Am  D  Em  Bm  C  G"},
  {"Bridge", "Am  D  Em  Bm  C  Am  D  Em"},
  {"Verse 2", "Am  D  Em  Bm  C  Am  D  Em  Bm  C  G  Am  D  Em  Bm  C  Am  D  Em  Bm  C  G"},
  {"Chorus", "Em  Bm  C  Em  Bm  C  G"},
  {"Bridge", "Am  D  Em  Bm  C  Am  D  Em  Bm  C  G"},
  {"Interlude", "Am  D  Em  Bm  C  Am  D  Em  Bm  C  Am  D  Em"},
  {"Bridge", "Am  D  Em  Bm  C  Am  D  Em"},
};

static const SongData SONG_LIBRARY[] = {
  {
    "zach-bryan-x-kacey-musgraves-type-beat-don-t-go",
    "Don't Go",
    "Zach Bryan x Kacey Musgraves Type Beat",
    -1,
    "E A D G B E",
    "Eb major",
    SONG_0_SECTIONS,
    10
  },
  {
    "adele-easy-on-me",
    "Easy On Me",
    "Adele",
    5,
    "E A D G B E",
    "F",
    SONG_1_SECTIONS,
    7
  },
  {
    "avicii-without-you",
    "Without You",
    "Avicii",
    -1,
    "E A D G B E",
    "D",
    SONG_2_SECTIONS,
    9
  },
  {
    "bastille-pompeii",
    "Pompeii",
    "Bastille",
    2,
    "E A D G B E",
    "F#m",
    SONG_3_SECTIONS,
    12
  },
  {
    "chris-stapleton-tennessee-whiskey",
    "Tennessee Whiskey",
    "Chris Stapleton",
    -1,
    "E A D G B E",
    "A",
    SONG_4_SECTIONS,
    7
  },
  {
    "chris-stapleton-white-horse",
    "White Horse",
    "Chris Stapleton",
    -1,
    "E A D G B E",
    "E",
    SONG_5_SECTIONS,
    6
  },
  {
    "cody-johnson-travelin-soldier",
    "Travelin Soldier",
    "Cody Johnson",
    2,
    "Db Ab Db Gb Bb Eb",
    "E",
    SONG_6_SECTIONS,
    8
  },
  {
    "darius-rucker-wagon-wheel",
    "Wagon Wheel",
    "Darius Rucker",
    2,
    "E A D G B E",
    "A",
    SONG_7_SECTIONS,
    8
  },
  {
    "eagles-hotel-california",
    "Hotel California",
    "Eagles",
    2,
    "E A D G B E",
    "Bm",
    SONG_8_SECTIONS,
    8
  },
  {
    "ella-langley-choosin-texas",
    "Choosin Texas",
    "Ella Langley",
    1,
    "E A D G B E",
    "Db",
    SONG_9_SECTIONS,
    8
  },
  {
    "gloria-gaynor-i-will-survive",
    "I Will Survive",
    "Gloria Gaynor",
    -1,
    "E A D G B E",
    "Am",
    SONG_10_SECTIONS,
    10
  },
  {
    "goo-goo-dolls-iris",
    "Iris",
    "Goo Goo Dolls",
    -1,
    "E A D G B E",
    "Bm",
    SONG_11_SECTIONS,
    12
  },
  {
    "hailee-steinfeld-feat-zedd-starving",
    "Starving",
    "Hailee Steinfeld feat. Zedd",
    4,
    "E A D G B E",
    "C",
    SONG_12_SECTIONS,
    5
  },
  {
    "imagine-dragons-demons",
    "Demons",
    "Imagine Dragons",
    3,
    "E A D G B E",
    "Eb",
    SONG_13_SECTIONS,
    8
  },
  {
    "james-blunt-youre-beautiful",
    "Youre Beautiful",
    "James Blunt",
    8,
    "E A D G B E",
    "G",
    SONG_14_SECTIONS,
    7
  },
  {
    "journey-dont-stop-believin",
    "Dont Stop Believin",
    "Journey",
    -1,
    "E A D G B E",
    "E",
    SONG_15_SECTIONS,
    6
  },
  {
    "journey-faithfully",
    "Faithfully",
    "Journey",
    -1,
    "Eb Ab Db Gb Bb Eb",
    "",
    SONG_16_SECTIONS,
    7
  },
  {
    "led-zeppelin-tangerine",
    "Tangerine",
    "Led Zeppelin",
    -1,
    "E A D G B E",
    "Am",
    SONG_17_SECTIONS,
    1
  },
  {
    "lynyrd-skynyrd-free-bird",
    "Free Bird",
    "Lynyrd Skynyrd",
    -1,
    "E A D G B E",
    "G",
    SONG_18_SECTIONS,
    1
  },
  {
    "martin-garrix-high-on-life",
    "High On Life",
    "Martin Garrix",
    -1,
    "E A D G B E",
    "A",
    SONG_19_SECTIONS,
    9
  },
  {
    "mumford-sons-i-will-wait",
    "I Will Wait",
    "Mumford & Sons",
    1,
    "E A D G B E",
    "Db",
    SONG_20_SECTIONS,
    10
  },
  {
    "noah-guthrie-love-on-the-brain",
    "Love On The Brain",
    "Noah Guthrie",
    -1,
    "E A D G B E",
    "G",
    SONG_21_SECTIONS,
    7
  },
  {
    "post-malone-chemical",
    "Chemical",
    "Post Malone",
    -1,
    "E A D G B E",
    "D",
    SONG_22_SECTIONS,
    9
  },
  {
    "post-malone-enough-is-enough",
    "Enough Is Enough",
    "Post Malone",
    -1,
    "E A D G B E",
    "G",
    SONG_23_SECTIONS,
    8
  },
  {
    "swedish-house-mafia-dont-you-worry-child",
    "Dont You Worry Child",
    "Swedish House Mafia",
    2,
    "E A D G B E",
    "",
    SONG_24_SECTIONS,
    5
  },
  {
    "the-allman-brothers-band-melissa",
    "Melissa",
    "The Allman Brothers Band",
    -1,
    "E A D G B E",
    "",
    SONG_25_SECTIONS,
    6
  },
  {
    "the-doobie-brothers-listen-to-the-music",
    "Listen To The Music",
    "The Doobie Brothers",
    -1,
    "E A D G B E",
    "",
    SONG_26_SECTIONS,
    8
  },
  {
    "the-killers-read-my-mind",
    "Read My Mind",
    "The Killers",
    1,
    "E A D G B E",
    "Am",
    SONG_27_SECTIONS,
    9
  },
  {
    "unknown-artist-the-cave-tab-by-mumford-sons-ultimate-guitar-com",
    "THE CAVE TAB by Mumford & Sons @ Ultimate-Guitar.Com",
    "Unknown Artist",
    2,
    "D A D F# A D",
    "",
    SONG_28_SECTIONS,
    3
  },
  {
    "vance-joy-georgia",
    "Georgia",
    "Vance Joy",
    4,
    "E A D G B E",
    "Abm",
    SONG_29_SECTIONS,
    10
  },
  {
    "zach-bryan-68-fastback",
    "68 Fastback",
    "Zach Bryan",
    -1,
    "E A D G B E",
    "",
    SONG_30_SECTIONS,
    3
  },
  {
    "zach-bryan-river-washed-hair",
    "River Washed Hair",
    "Zach Bryan",
    -1,
    "E A D G B E",
    "C",
    SONG_31_SECTIONS,
    7
  },
  {
    "zach-bryan-shes-alright",
    "Shes Alright",
    "Zach Bryan",
    2,
    "E A D G B E",
    "",
    SONG_32_SECTIONS,
    6
  },
  {
    "zedd-elley-duh-happy-now",
    "Happy Now",
    "Zedd, Elley Duhé",
    2,
    "E A D G B E",
    "E",
    SONG_33_SECTIONS,
    11
  },
  {
    "zedd-feat-foxes-clarity",
    "Clarity",
    "Zedd feat. Foxes",
    1,
    "E A D G B E",
    "G",
    SONG_34_SECTIONS,
    10
  },
};

static const uint16_t SONG_LIBRARY_COUNT = 35;
