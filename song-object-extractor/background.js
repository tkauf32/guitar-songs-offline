// One toolbar click immediately extracts and downloads the current visible song.
chrome.action.onClicked.addListener(async (tab) => {
  try {
    const [{ result }] = await chrome.scripting.executeScript({
      target: { tabId: tab.id },
      func: extractSongObject
    });

    if (!result?.ok) {
      if (result?.debug) await downloadDebug(result.debug, tab);
      throw new Error(result?.error || "Could not extract song.");
    }

    const song = result.song;
    await downloadJSON(
      song,
      `Songbook/${slug(song.artist || "unknown-artist")}--${slug(song.title || "untitled")}.json`
    );
    await setBadge(tab.id, "✓", "#2e7d32", 1800);
  } catch (error) {
    console.error("Song Object Extractor:", error);
    await setBadge(tab.id, "!", "#b71c1c", 3500);
  }
});

async function downloadJSON(data, filename) {
  const json = JSON.stringify(data, null, 2);
  const url = "data:application/json;charset=utf-8," + encodeURIComponent(json);

  await chrome.downloads.download({
    url,
    filename,
    saveAs: false,
    conflictAction: "uniquify"
  });
}

async function downloadDebug(debug, tab) {
  await downloadJSON(debug, `Songbook/debug-${Date.now()}.json`);
  await setBadge(tab.id, "DBG", "#8a4b00", 4000);
}

async function setBadge(tabId, text, color, delay) {
  await chrome.action.setBadgeText({ tabId, text });
  await chrome.action.setBadgeBackgroundColor({ tabId, color });
  setTimeout(() => chrome.action.setBadgeText({ tabId, text: "" }), delay);
}

function slug(value) {
  return String(value).toLowerCase().normalize("NFKD")
    .replace(/[^\w\s-]/g, "").trim().replace(/[\s_-]+/g, "-")
    .replace(/^-+|-+$/g, "").slice(0, 90);
}

function extractSongObject() {
  const cleanText = value => String(value || "")
    .replace(/\u00a0/g, " ")
    .replace(/\r/g, "")
    .replace(/[ \t]+\n/g, "\n");

  try {
    const bodyText = cleanText(document.body?.innerText);
    const titleLine = bodyText.match(/^(.+?)\s+Chords by\s+(.+)$/mi);
    const title = titleLine?.[1]?.trim() || document.title.split(/\s+Chords/i)[0].trim();
    const artist = titleLine?.[2]?.trim() || "";

    const field = name => {
      const escaped = name.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
      return bodyText.match(new RegExp(`^${escaped}:\\s*(.+)$`, "mi"))?.[1]?.trim() || null;
    };

    const candidate = findBestTabCandidate();
    const sourceText = candidate?.text || bodyText;
    const extracted = isolateTab(sourceText);

    if (!extracted.rawTab) {
      return {
        ok: false,
        error: extracted.error || "Chord sheet not found.",
        debug: makeDebug(bodyText, candidate, extracted)
      };
    }

    const sections = parseSections(extracted.rawTab);
    if (!sections.some(s => s.lines.some(l => l.type === "chords"))) {
      return {
        ok: false,
        error: "Text was isolated, but no chord lines were recognized. A debug JSON was downloaded.",
        debug: makeDebug(bodyText, candidate, extracted)
      };
    }

    return {
      ok: true,
      song: {
        schemaVersion: 3,
        source: {
          provider: location.hostname,
          url: location.href,
          capturedAt: new Date().toISOString(),
          extractionMethod: `${candidate?.method || "body"}:${extracted.method}`
        },
        title,
        artist,
        metadata: {
          key: field("Key"),
          capo: field("Capo"),
          tuning: field("Tuning"),
          difficulty: field("Difficulty")
        },
        sections,
        rawTab: extracted.rawTab
      }
    };

    function findBestTabCandidate() {
      const selectors = [
        "pre",
        "[class*='tab-content']",
        "[class*='TabContent']",
        "[class*='wiki']",
        "[data-testid*='tab']",
        "article",
        "main"
      ];

      const seen = new Set();
      const candidates = [];

      for (const selector of selectors) {
        for (const el of document.querySelectorAll(selector)) {
          if (seen.has(el)) continue;
          seen.add(el);

          const text = cleanText(el.innerText).trim();
          if (text.length < 120) continue;

          const chordLines = text.split("\n").filter(line => parseChordLine(line).length).length;
          const sectionHits = (text.match(/^\s*(?:\[[^\]]+\]|Intro|Verse|Chorus|Bridge|Outro|Pre[- ]?Chorus)\s*:?\s*$/gmi) || []).length;
          const uiPenalty = (text.match(/DOWNLOAD PDF|RELATED TABS|SIGN UP|LOG IN|AUTOSCROLL|REPORT BAD TAB/gi) || []).length;
          const score = chordLines * 20 + sectionHits * 8 - uiPenalty * 15 - Math.max(0, text.length - 25000) / 1000;

          if (chordLines >= 2) candidates.push({ text, score, method: selector, chordLines, sectionHits });
        }
      }

      candidates.sort((a, b) => b.score - a.score);
      return candidates[0] || null;
    }

    function isolateTab(text) {
      const lines = text.split("\n");
      const offsets = [];
      let offset = 0;
      for (const line of lines) {
        offsets.push(offset);
        offset += line.length + 1;
      }

      const endLinePatterns = [
        /^X$/,
        /^Create correction$/i,
        /^Please rate this tab$/i,
        /^FONT$/i,
        /^AUTOSCROLL$/i,
        /^REPORT BAD TAB$/i,
        /^RELATED TABS$/i,
        /^\d+\s+COMMENT/i,
        /^SIGN UP$/i
      ];

      let startLine = -1;

      // Normal section heading followed by chords.
      for (let i = 0; i < lines.length; i++) {
        if (isSectionHeading(lines[i]) && hasChordNearby(lines, i + 1, 10)) {
          startLine = i;
          break;
        }
      }

      // First credible musical block: at least two chord lines within eight lines.
      if (startLine < 0) {
        for (let i = 0; i < lines.length; i++) {
          if (!parseChordLine(lines[i]).length) continue;
          const window = lines.slice(i, i + 8);
          const chordCount = window.filter(line => parseChordLine(line).length).length;
          const lyricCount = window.filter(looksLikeLyric).length;
          if (chordCount >= 2 && lyricCount >= 1) {
            startLine = i > 0 && isSectionHeading(lines[i - 1]) ? i - 1 : i;
            break;
          }
        }
      }

      if (startLine < 0) {
        return { rawTab: "", method: "none", error: "No credible musical block was detected." };
      }

      let endLine = lines.length;
      for (let i = startLine + 1; i < lines.length; i++) {
        if (endLinePatterns.some(re => re.test(lines[i].trim()))) {
          endLine = i;
          break;
        }
      }

      const rawTab = lines.slice(startLine, endLine)
        .join("\n")
        .replace(/\n{4,}/g, "\n\n\n")
        .trim();

      return { rawTab, method: startLine === 0 ? "candidate-start" : "musical-block" };
    }

    function parseSections(raw) {
      const lines = raw.split("\n");
      const sections = [];
      let current = null;

      const openSection = label => {
        current = {
          id: normalizeSectionId(label, sections),
          label: label.trim(),
          lines: [],
          progression: []
        };
        sections.push(current);
      };

      for (const originalLine of lines) {
        if (isSectionHeading(originalLine)) {
          openSection(stripSectionHeading(originalLine));
          continue;
        }

        if (!current) openSection("Song");

        const chords = parseChordLine(originalLine);
        const type = chords.length ? "chords" : (originalLine.trim() ? "lyrics" : "blank");
        current.lines.push({ type, text: originalLine, chords });

        if (chords.length) {
          current.progression.push(...chords.map(x => x.chord));
        }
      }

      return sections;
    }

    function isSectionHeading(line) {
      const t = line.trim();
      if (/^\[[^\]]{1,40}\]$/.test(t)) return true;
      return /^(Intro|Verse(?:\s+\d+)?|Pre[- ]?Chorus|Chorus|Bridge|Outro|Interlude|Instrumental|Solo|Refrain|Hook|Break|Part(?:\s+[A-Z0-9]+)?)(?:\s*[:\-])?$/i.test(t);
    }

    function stripSectionHeading(line) {
      return line.trim().replace(/^\[|\]$/g, "").replace(/[:\-]\s*$/, "").trim();
    }

    function hasChordNearby(lines, start, distance) {
      return lines.slice(start, start + distance).some(line => parseChordLine(line).length);
    }

    function looksLikeLyric(line) {
      const t = line.trim();
      return t.length >= 5 &&
        /[a-z]{3}/i.test(t) &&
        !/^(FONT|CHORDS|AUTOSCROLL|TRANSPOSE|PRINT|REPORT|DOWNLOAD|RELATED|SIGN UP|LOG IN)/i.test(t);
    }

    function normalizeSectionId(label, sections) {
      const base = label.toLowerCase()
        .replace(/pre[\s-]?chorus/g, "prechorus")
        .replace(/[^a-z0-9]+/g, "-")
        .replace(/^-|-$/g, "") || "section";
      const count = sections.filter(s => s.id === base || s.id.startsWith(base + "-")).length;
      return count ? `${base}-${count + 1}` : base;
    }

    function parseChordLine(line) {
      const tokenRE = /[A-G](?:#|b)?(?:maj|min|m|dim|aug|sus|add|no|M)?(?:\d+)?(?:[#b]\d+)?(?:\([^)]+\))?(?:\/[A-G](?:#|b)?)?/g;
      const tokens = [];
      let match;

      while ((match = tokenRE.exec(line)) !== null) {
        const before = line.slice(Math.max(0, match.index - 1), match.index);
        const after = line.slice(match.index + match[0].length, match.index + match[0].length + 1);
        if (before && !/[\s|:([/-]/.test(before)) continue;
        if (after && !/[\s|:)\]/-]/.test(after)) continue;
        tokens.push({ chord: match[0], column: match.index });
      }

      if (!tokens.length) return [];

      let residue = line;
      for (const token of [...tokens].reverse()) {
        residue = residue.slice(0, token.column) + " ".repeat(token.chord.length) + residue.slice(token.column + token.chord.length);
      }
      residue = residue.replace(/[|:()[\]xX0-9\-–—./\\,\s]/g, "");
      return residue ? [] : tokens;
    }

    function makeDebug(bodyText, candidate, extracted) {
      return {
        url: location.href,
        title: document.title,
        error: extracted?.error || null,
        candidate: candidate ? {
          method: candidate.method,
          score: candidate.score,
          chordLines: candidate.chordLines,
          sectionHits: candidate.sectionHits,
          text: candidate.text.slice(0, 30000)
        } : null,
        bodyText: bodyText.slice(0, 50000)
      };
    }
  } catch (error) {
    return {
      ok: false,
      error: error.message,
      debug: {
        url: location.href,
        title: document.title,
        stack: error.stack || null,
        bodyText: cleanText(document.body?.innerText).slice(0, 50000)
      }
    };
  }
}
