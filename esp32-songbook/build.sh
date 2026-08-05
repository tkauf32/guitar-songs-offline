#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
FQBN="${FQBN:-esp32:esp32:esp32s3}"
PORT="${PORT:-}"

python3 "${ROOT_DIR}/generate_song_data.py"
arduino-cli compile --fqbn "${FQBN}" "${ROOT_DIR}"

if [[ -n "${PORT}" ]]; then
  arduino-cli upload -p "${PORT}" --fqbn "${FQBN}" "${ROOT_DIR}"
fi
