#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
linkserver="${LINKSERVER:-LinkServer}"
device="${LINKSERVER_DEVICE:-MK22FN512xxx12}"
image="${1:-${project_root}/build/debug/epp-tinyk22.s19}"

if ! command -v "$linkserver" >/dev/null 2>&1; then
    printf 'LinkServer not found. Set LINKSERVER to its executable path.\n' >&2
    exit 1
fi

if [[ ! -f "$image" ]]; then
    printf 'Firmware image not found: %s\n' "$image" >&2
    exit 1
fi

flash_options=()
if [[ -n "${LINKSERVER_PROBE:-}" ]]; then
    flash_options+=(--probe "$LINKSERVER_PROBE")
fi

printf 'Programming %s with %s\n' "$device" "$image"
"$linkserver" flash "${flash_options[@]}" "$device" load "$image"