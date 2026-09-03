#!/usr/bin/env bash
#
# package-ios-deploy.sh — one-shot iOS pipeline (lives inside the BeamPlatformNotifications plugin):
#   1. Package the iOS client (UAT BuildCookRun)
#   2. Graft + sign the closed-app Notification Service Extension (add-nse.sh, sibling)
#   3. Install the .app to a device (pre-selected via --device, or interactive prompt)
#
# Project-agnostic: the project context is passed in (the script lives in the plugin, not the
# project). The editor toolbar button passes everything; you can also run it by hand.
#
# Usage:
#   ./package-ios-deploy.sh --project-dir <dir> [--uproject <x.uproject>] [--target <name>]
#                           [--device <UDID>] [--config Development] [--ue-root <dir>]
#
set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=""
UPROJECT=""
TARGET=""
UE_ROOT="${UE_ROOT:-/Users/Shared/Epic Games/UE_5.6}"
CONFIG="${CONFIG:-Development}"
DEVICE=""   # --device <UDID>: pre-selected (skips the interactive prompt)

while [[ $# -gt 0 ]]; do
  case "$1" in
    --project-dir) PROJECT_DIR="$2"; shift 2 ;;
    --uproject) UPROJECT="$2"; shift 2 ;;
    --target) TARGET="$2"; shift 2 ;;
    --device) DEVICE="$2"; shift 2 ;;
    --config) CONFIG="$2"; shift 2 ;;
    --ue-root) UE_ROOT="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 1 ;;
  esac
done

log()  { printf '\033[0;36m[ios]\033[0m %s\n' "$*"; }
warn() { printf '\033[0;33m[warn]\033[0m %s\n' "$*"; }
die()  { printf '\033[0;31m[err]\033[0m %s\n' "$*" >&2; [[ -t 0 ]] && read -r -p "Press return to close..." _; exit 1; }

# Resolve project context (fall back to sensible defaults if only --project-dir was given).
[[ -n "$PROJECT_DIR" ]] || die "Missing --project-dir (the Unreal project root)."
PROJECT_DIR="$(cd "$PROJECT_DIR" && pwd)" || die "Bad --project-dir."
[[ -n "$UPROJECT" ]] || UPROJECT="$(find "$PROJECT_DIR" -maxdepth 1 -name '*.uproject' | head -1)"
[[ -n "$TARGET" ]]   || TARGET="$(basename "${UPROJECT%.uproject}")"
ARCHIVE="$PROJECT_DIR/Binaries/IOS/Archive"

[[ -f "$UPROJECT" ]] || die "uproject not found at $UPROJECT"
[[ -d "$UE_ROOT/Engine" ]] || die "Unreal Engine not found at '$UE_ROOT' (set UE_ROOT env var)."
RUNUAT="$UE_ROOT/Engine/Build/BatchFiles/RunUAT.sh"
[[ -x "$RUNUAT" ]] || die "RunUAT.sh not found/executable at $RUNUAT"

# ── 1. Package iOS ──────────────────────────────────────────────────────────
log "Packaging iOS ($CONFIG)... (this can take several minutes)"
mkdir -p "$ARCHIVE"
"$RUNUAT" BuildCookRun \
  -project="$UPROJECT" -nop4 -utf8output \
  -platform=IOS -clientconfig="$CONFIG" -target="$TARGET" \
  -build -cook -stage -pak -package -archive -archivedirectory="$ARCHIVE" \
  || die "iOS packaging failed (see log above)."

# ── 2. Locate the produced .app (devicectl installs a .app directly) ────────
APP="$(find "$PROJECT_DIR/Binaries/IOS" "$ARCHIVE" -maxdepth 4 -name '*.app' -type d -print0 2>/dev/null \
        | xargs -0 ls -dt 2>/dev/null | head -1)"
[[ -d "$APP" ]] || die "Could not find a packaged .app under Binaries/IOS or $ARCHIVE."
log "Packaged: $APP"

# ── 3. Embed + sign the Notification Service Extension into the .app ────────
log "Embedding the Notification Service Extension..."
"$SCRIPT_DIR/add-nse.sh" --app "$APP" --project-dir "$PROJECT_DIR" || die "add-nse.sh failed."

# ── 4. Resolve the target device ────────────────────────────────────────────
command -v xcrun >/dev/null || die "xcrun not found (install Xcode)."

UDID=""
if [[ -n "$DEVICE" ]]; then
  # Pre-selected in the Unreal editor — no interactive prompt.
  UDID="$DEVICE"
  log "Target device (from editor): $UDID"
else
  DEVJSON="$(mktemp)"; trap 'rm -f "$DEVJSON"' EXIT
  xcrun devicectl list devices --json-output "$DEVJSON" >/dev/null 2>&1 || die "devicectl list failed."

  # Parse devicectl output into PARALLEL arrays (bash 3.2-safe: no `mapfile`, no fragile
  # tab-pattern stripping). Each python line is "<udid>\t<label>"; IFS=$'\t' read splits it.
  DEV_UDIDS=(); DEV_LABELS=()
  while IFS=$'\t' read -r udid label; do
    [[ -n "$udid" ]] || continue
    DEV_UDIDS+=("$udid")
    DEV_LABELS+=("$label")
  done < <(python3 - "$DEVJSON" <<'PY'
import json, sys
data = json.load(open(sys.argv[1]))
for d in data.get("result", {}).get("devices", []):
    hw = d.get("hardwareProperties", {})
    dp = d.get("deviceProperties", {})
    conn = d.get("connectionProperties", {})
    # only physical iPhones/iPads
    if hw.get("platform","").lower() not in ("ios","ipados"):
        continue
    udid = hw.get("udid","")
    name = dp.get("name", hw.get("marketingName","device"))
    state = conn.get("tunnelState", conn.get("pairingState",""))
    if udid:
        print(f"{udid}\t{name} [{state}]")
PY
)

  [[ ${#DEV_UDIDS[@]} -gt 0 ]] || die "No iOS devices found. Connect/unlock your device and trust this Mac."

  if [[ ${#DEV_UDIDS[@]} -eq 1 ]]; then
    UDID="${DEV_UDIDS[0]}"
    log "Using the only connected device: ${DEV_LABELS[0]}"
  else
    echo "Connected devices:"
    for ((i=0; i<${#DEV_UDIDS[@]}; i++)); do echo "  $((i+1))) ${DEV_LABELS[$i]}"; done
    read -r -p "Select device [1-${#DEV_UDIDS[@]}]: " choice
    if [[ "$choice" =~ ^[0-9]+$ ]] && (( choice >= 1 && choice <= ${#DEV_UDIDS[@]} )); then
      UDID="${DEV_UDIDS[$((choice-1))]}"
    else
      die "Invalid selection."
    fi
  fi
fi
[[ -n "$UDID" ]] || die "No device UDID resolved."

# ── 5. Install to the device ────────────────────────────────────────────────
log "Installing to device ${UDID}..."
xcrun devicectl device install app --device "${UDID}" "${APP}" || die "Install failed."
log "Installed. Launch the app on the device."
# Success marker the editor watches for (FMonitoredProcess can't always recover bash's exit code).
echo "BMN_PIPELINE_SUCCESS"
[[ -t 0 ]] && read -r -p "Done - press return to close..." _ || true
