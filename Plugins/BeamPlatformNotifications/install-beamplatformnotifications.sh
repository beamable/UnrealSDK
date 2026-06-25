#!/usr/bin/env bash
#
# install-beamplatformnotifications.sh — generate a self-contained BeamPlatformNotifications
# Unreal plugin from the Beamable native-library source, and install it into an Unreal project.
#
# Project-agnostic & shareable: copy this script into any UE project and run it. It prompts
# (showing detected defaults) for the project-specific values and writes them into the project's
# Config/DefaultEngine.ini. Nothing project-specific is baked into the plugin.
#
# Usage:
#   ./install-beamplatformnotifications.sh --source <nativeLibraries> [--project <dir>]
#   ./install-beamplatformnotifications.sh --source <nativeLibraries> --generate-only <outDir>
#
#   --source <dir>          Path to the BeamableProduct/nativeLibraries checkout (required).
#   --project <dir>         Target Unreal project root (default: this script's directory).
#   --generate-only <dir>   Just emit the self-contained plugin folder into <dir> and stop.
#
set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOURCE=""
PROJECT="$SCRIPT_DIR"
GEN_ONLY=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --source) SOURCE="$2"; shift 2 ;;
    --project) PROJECT="$2"; shift 2 ;;
    --generate-only) GEN_ONLY="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 1 ;;
  esac
done

log()  { printf '\033[0;36m[bpn]\033[0m %s\n' "$*"; }
warn() { printf '\033[0;33m[warn]\033[0m %s\n' "$*"; }
die()  { printf '\033[0;31m[err]\033[0m %s\n' "$*" >&2; exit 1; }

[[ -n "$SOURCE" ]] || die "Missing --source <nativeLibraries>."
[[ -d "$SOURCE" ]] || die "Source not found: $SOURCE"

# --- source layout ----------------------------------------------------------
# The master plugin already ships its native binaries under ThirdParty/ (staged by the repo's
# dev-native.sh): ThirdParty/BeamableNotifications.embeddedframework.zip (iOS dynamic framework)
# and ThirdParty/Android/beamable-notifications-release.aar (consumed flat by the APL's
# <AARImports> via a Gradle flatDir repo). So we copy the whole plugin, ThirdParty included.
MASTER="$SOURCE/EnginePlugins/Unreal"                      # master plugin (sources + Scripts + ThirdParty + docs)
NSE_SRC="$SOURCE/iOS/BeamableNotifications/extension"

[[ -f "$MASTER/BeamPlatformNotifications.uplugin" ]] || die "Master plugin not found at $MASTER (expected BeamPlatformNotifications.uplugin). Update the native-library source first."

# --- 1. GENERATE the self-contained plugin ----------------------------------
STAGE="$(mktemp -d)/BeamPlatformNotifications"
mkdir -p "$STAGE"
log "Generating self-contained plugin from $MASTER ..."
# Plugin sources + committed ThirdParty binaries (skip only the build outputs).
( cd "$MASTER" && find . \( -path './Intermediate' -o -path './Binaries' \) -prune -o -type f -print0 \
    | while IFS= read -r -d '' f; do mkdir -p "$STAGE/$(dirname "$f")"; cp "$f" "$STAGE/$f"; done )

[[ -f "$STAGE/ThirdParty/BeamableNotifications.embeddedframework.zip" ]] \
  || warn "iOS framework missing (ThirdParty/BeamableNotifications.embeddedframework.zip) — run dev-native.sh on macOS to stage it; iOS link will fail until then."
[[ -f "$STAGE/ThirdParty/Android/beamable-notifications-release.aar" ]] \
  || warn "Android .aar missing (ThirdParty/Android/beamable-notifications-release.aar) — run dev-native.sh to stage it; Android build will fail until then."

# Notification Service Extension sources (optional full-featured NSE; the editor button's
# add-nse.sh builds a self-contained one and does not require these).
if [[ -d "$NSE_SRC" ]]; then
  rm -rf "$STAGE/Extension"; mkdir -p "$STAGE/Extension"; cp -R "$NSE_SRC"/. "$STAGE/Extension/"
else
  warn "NSE sources not found ($NSE_SRC)."
fi

find "$STAGE/Scripts" -name '*.sh' -exec chmod +x {} \; 2>/dev/null || true
log "Self-contained plugin assembled."

if [[ -n "$GEN_ONLY" ]]; then
  mkdir -p "$GEN_ONLY"
  rm -rf "$GEN_ONLY/BeamPlatformNotifications"
  cp -R "$STAGE" "$GEN_ONLY/BeamPlatformNotifications"
  log "Emitted plugin → $GEN_ONLY/BeamPlatformNotifications (generate-only; not installed)."
  exit 0
fi

# --- 2. INSTALL into the target project --------------------------------------
[[ -d "$PROJECT" ]] || die "Project dir not found: $PROJECT"
UPROJECT="$(find "$PROJECT" -maxdepth 1 -name '*.uproject' | head -1)"
[[ -f "$UPROJECT" ]] || die "No .uproject in $PROJECT"
INI="$PROJECT/Config/DefaultEngine.ini"
DEST="$PROJECT/Plugins/BeamPlatformNotifications"

log "Installing into $PROJECT ..."
rm -rf "$DEST"; mkdir -p "$PROJECT/Plugins"; cp -R "$STAGE" "$DEST"
rm -rf "$DEST/Intermediate" "$DEST/Binaries"

# Enable the plugin in the .uproject
python3 - "$UPROJECT" <<'PY'
import json,sys
p=sys.argv[1]; d=json.load(open(p)); pl=d.setdefault("Plugins",[])
if not any(x.get("Name")=="BeamPlatformNotifications" for x in pl):
    pl.append({"Name":"BeamPlatformNotifications","Enabled":True})
else:
    for x in pl:
        if x.get("Name")=="BeamPlatformNotifications": x["Enabled"]=True
json.dump(d,open(p,"w"),indent=2); open(p,"a").write("\n")
PY

# --- 3. Detect defaults + prompt --------------------------------------------
ini_get() { # section key
  [[ -f "$INI" ]] || return 0
  awk -v s="[$1]" -v k="$2" '
    $0==s {ins=1; next} /^\[/ {ins=0}
    ins && $0 ~ "^[[:space:]]*"k"=" { sub("^[^=]*=",""); gsub("\r",""); print; exit }' "$INI"
}
ask() { # varname prompt default
  local def="$3" ans=""
  if [[ -t 0 ]]; then read -r -p "$2 [$def]: " ans; fi
  printf -v "$1" '%s' "${ans:-$def}"
}

DET_BUNDLE="$(ini_get '/Script/IOSRuntimeSettings.IOSRuntimeSettings' BundleIdentifier)"
DET_TEAM="$(ini_get '/Script/MacTargetPlatform.XcodeProjectSettings' CodeSigningTeam)"
DEF_GROUP="$(ini_get '/Script/BeamPlatformNotifications.Settings' AppGroup)"; DEF_GROUP="${DEF_GROUP:-group.com.beamable.notifications}"
DEF_SCHEME="$(ini_get 'BeamPlatformNotifications' DeepLinkScheme)"; DEF_SCHEME="${DEF_SCHEME:-beamnotify}"
DEF_ENDPOINT="$(ini_get 'BeamPlatformNotifications' AnalyticsEndpoint)"
DEF_FCM="$(ini_get 'BeamPlatformNotifications' bUseFcm)"; DEF_FCM="${DEF_FCM:-False}"

log "Detected from project config:"
log "  iOS BundleIdentifier : ${DET_BUNDLE:-<unset>}"
log "  iOS CodeSigningTeam  : ${DET_TEAM:-<unset>}"
[[ -n "$DET_BUNDLE" ]] || warn "No iOS BundleIdentifier set in the project — set one in Project Settings ▸ iOS."
[[ -n "$DET_TEAM" ]]   || warn "No iOS CodeSigningTeam set — set your Apple team in Project Settings ▸ iOS."

echo "Enter values for this project (press return to accept the [default]):"
ask APPGROUP   "  App Group id" "$DEF_GROUP"
ask SCHEME     "  Deep-link URL scheme" "$DEF_SCHEME"
ask ENDPOINT   "  Closed-app analytics webhook (blank = disabled)" "$DEF_ENDPOINT"
ask USEFCM     "  Enable Android FCM remote push? (True/False)" "$DEF_FCM"

# --- 4. Write config ---------------------------------------------------------
python3 - "$INI" \
  "/Script/BeamPlatformNotifications.Settings|AppGroup|$APPGROUP" \
  "BeamPlatformNotifications|DeepLinkScheme|$SCHEME" \
  "BeamPlatformNotifications|AnalyticsEndpoint|$ENDPOINT" \
  "BeamPlatformNotifications|bUseFcm|$USEFCM" \
  "/Script/IOSRuntimeSettings.IOSRuntimeSettings|bEnableRemoteNotificationsSupport|True" <<'PY'
import sys,re,io
ini=sys.argv[1]; triples=[a.split("|",2) for a in sys.argv[2:]]
try: text=open(ini).read()
except FileNotFoundError: text=""
lines=text.splitlines()
def find_section(name):
    for i,l in enumerate(lines):
        if l.strip()==f"[{name}]": return i
    return -1
def section_end(start):
    j=start+1
    while j<len(lines) and not lines[j].lstrip().startswith("["): j+=1
    return j
for section,key,val in triples:
    si=find_section(section)
    if si<0:
        if lines and lines[-1].strip()!="": lines.append("")
        lines.append(f"[{section}]"); lines.append(f"{key}={val}"); continue
    end=section_end(si); rx=re.compile(r"^\s*"+re.escape(key)+r"=")
    for k in range(si+1,end):
        if rx.match(lines[k]): lines[k]=f"{key}={val}"; break
    else:
        lines.insert(end, f"{key}={val}")
open(ini,"w").write("\n".join(lines)+"\n")
print("  config written")
PY

# --- 5. Manual steps ---------------------------------------------------------
cat <<EOF

$(log "Installed. Remaining one-time manual steps:")
  • iOS push entitlement: this project signs via PremadeIOSEntitlements? If so, add
    '<key>aps-environment</key><string>development</string>' to that .entitlements file
    (bEnableRemoteNotificationsSupport alone is ignored when a premade entitlements file is set).
  • iOS closed-app analytics: the editor button's add-nse.sh grafts a self-contained NSE
    (no App Group needed). See Plugins/BeamPlatformNotifications/NSE-SETUP.md.
  • Android FCM (only if you set bUseFcm=True): add Build/Android/google-services.json.
  • Build the editor, then use the "iOS + NSE → Device" toolbar button to package + deploy.
EOF
