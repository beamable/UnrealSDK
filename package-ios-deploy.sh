#!/usr/bin/env bash
#
# package-ios-deploy.sh — one-shot iOS pipeline for the notification test:
#   1. Package the iOS client (UAT BuildCookRun → .ipa)
#   2. Graft + sign the closed-app Notification Service Extension (add-nse.sh)
#   3. Pick a connected device and install the .ipa to it
#
# Invoked by the "iOS + NSE → Device" button added to the Unreal editor toolbar
# (BeamNotifTestEditor module), or run directly. Runs interactively so you can pick the device.
#
set -uo pipefail

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
UPROJECT="$PROJECT_DIR/BeamableUnreal.uproject"
UE_ROOT="${UE_ROOT:-/Users/Shared/Epic Games/UE_5.6}"
CONFIG="${CONFIG:-Development}"
TARGET="${TARGET:-BeamableUnreal}"
DEVICE=""   # --device <UDID>: pre-selected by the editor button; skips the interactive prompt

while [[ $# -gt 0 ]]; do
  case "$1" in
    --device) DEVICE="$2"; shift 2 ;;
    --config) CONFIG="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 1 ;;
  esac
done
ARCHIVE="$PROJECT_DIR/Binaries/IOS/Archive"

log()  { printf '\033[0;36m[ios]\033[0m %s\n' "$*"; }
warn() { printf '\033[0;33m[warn]\033[0m %s\n' "$*"; }
die()  { printf '\033[0;31m[err]\033[0m %s\n' "$*" >&2; [[ -t 0 ]] && read -r -p "Press return to close..." _; exit 1; }

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
"$PROJECT_DIR/add-nse.sh" --app "$APP" || die "add-nse.sh failed."

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
