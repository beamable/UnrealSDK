#!/usr/bin/env bash
#
# setup-unreal.sh — one-shot setup for the BeamableNotifications native plugin + the
# standalone notification-test plugin in this Unreal project.
#
# It stages the prebuilt native binaries the plugin needs (iOS framework, Android .aar,
# NSE sources), builds the local maven repo the Android APL imports, patches
# Config/DefaultEngine.ini, enables the plugins in the .uproject, and prints the remaining
# manual steps it cannot perform. Safe to re-run (idempotent).
#
# Usage:
#   ./setup-unreal.sh [--rebuild] [--native-lib /path/to/nativeLibraries]
#     --rebuild      Rebuild the iOS xcframework and Android .aar from source first.
#     --native-lib   Path to the BeamableProduct/nativeLibraries checkout.
#
set -euo pipefail

# --- config -----------------------------------------------------------------
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
NATIVE_LIB="${NATIVE_LIB:-/Users/felipearruda/Documents/Work/BeamableProduct/nativeLibraries}"
REBUILD=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    --rebuild) REBUILD=1; shift ;;
    --native-lib) NATIVE_LIB="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 1 ;;
  esac
done

PLUGIN_DIR="$PROJECT_DIR/Plugins/BeamPlatformNotifications"
IOS_BUILD="$NATIVE_LIB/iOS/BeamableNotifications/build"
IOS_EXTENSION="$NATIVE_LIB/iOS/BeamableNotifications/extension"
ANDROID_DIR="$NATIVE_LIB/Android/BeamableNotifications"
AAR_SRC="$ANDROID_DIR/reactnative/android/libs/beamable-notifications-release.aar"
UPROJECT="$PROJECT_DIR/BeamableUnreal.uproject"
ENGINE_INI="$PROJECT_DIR/Config/DefaultEngine.ini"

log()  { printf '\033[0;36m[setup]\033[0m %s\n' "$*"; }
warn() { printf '\033[0;33m[warn]\033[0m %s\n' "$*"; }
die()  { printf '\033[0;31m[err]\033[0m %s\n' "$*" >&2; exit 1; }

# --- 0. sanity --------------------------------------------------------------
[[ -d "$NATIVE_LIB" ]] || die "Native library not found at: $NATIVE_LIB (pass --native-lib)"
[[ -f "$UPROJECT" ]]   || die "Not an Unreal project dir (no BeamableUnreal.uproject): $PROJECT_DIR"
[[ -d "$PLUGIN_DIR/Source" ]] || die "BeamableNotifications plugin source missing — is this repo set up?"

# --- 1. optional rebuild of native binaries ---------------------------------
if [[ "$REBUILD" == "1" ]]; then
  log "Rebuilding iOS framework (dynamic) …"
  ( cd "$NATIVE_LIB/iOS/BeamableNotifications" && ./scripts/build-xcframework-dynamic.sh ) || warn "iOS rebuild failed"
  log "Rebuilding Android .aar …"
  ( cd "$ANDROID_DIR" && ./gradlew :notifications:assembleRelease ) || warn "Android rebuild failed"
fi

# --- 2. clean stale stub artifacts ------------------------------------------
log "Cleaning stale build artifacts in the plugin …"
rm -rf "$PLUGIN_DIR/Intermediate" "$PLUGIN_DIR/Binaries"
find "$PLUGIN_DIR" -name '.DS_Store' -delete 2>/dev/null || true

# --- 3. stage iOS framework -------------------------------------------------
mkdir -p "$PLUGIN_DIR/ThirdParty"
IOS_ZIP="$IOS_BUILD/BeamableNotifications.embeddedframework.zip"
if [[ -f "$IOS_ZIP" ]]; then
  log "Staging iOS framework → ThirdParty/"
  cp -f "$IOS_ZIP" "$PLUGIN_DIR/ThirdParty/BeamableNotifications.embeddedframework.zip"
else
  warn "iOS framework not found ($IOS_ZIP). Run with --rebuild or build-xcframework-dynamic.sh. iOS link will fail until staged."
fi

# --- 4. stage Notification Service Extension sources ------------------------
if [[ -d "$IOS_EXTENSION" ]]; then
  log "Staging Notification Service Extension sources → Extension/"
  rm -rf "$PLUGIN_DIR/Extension"
  mkdir -p "$PLUGIN_DIR/Extension"
  cp -R "$IOS_EXTENSION"/. "$PLUGIN_DIR/Extension/"
else
  warn "NSE sources not found ($IOS_EXTENSION). Closed-app analytics extension won't be staged."
fi

# --- 5. build the Android maven repo the APL imports ------------------------
if [[ -f "$AAR_SRC" ]]; then
  REPO="$PLUGIN_DIR/ThirdParty/Android/repository/com/beamable/beamable-notifications/1.0.0"
  log "Staging Android .aar into local maven repo → ThirdParty/Android/repository"
  mkdir -p "$REPO"
  cp -f "$AAR_SRC" "$REPO/beamable-notifications-1.0.0.aar"
  cat > "$REPO/beamable-notifications-1.0.0.pom" <<'POM'
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.beamable</groupId>
  <artifactId>beamable-notifications</artifactId>
  <version>1.0.0</version>
  <packaging>aar</packaging>
  <dependencies>
    <dependency>
      <groupId>androidx.core</groupId>
      <artifactId>core-ktx</artifactId>
      <version>1.12.0</version>
      <scope>compile</scope>
    </dependency>
    <dependency>
      <groupId>org.jetbrains.kotlin</groupId>
      <artifactId>kotlin-stdlib</artifactId>
      <version>1.9.22</version>
      <scope>compile</scope>
    </dependency>
    <dependency>
      <groupId>com.google.firebase</groupId>
      <artifactId>firebase-messaging</artifactId>
      <version>24.1.0</version>
      <scope>compile</scope>
    </dependency>
  </dependencies>
</project>
POM
else
  warn "Android .aar not found ($AAR_SRC). Run with --rebuild. Android build will fail until staged."
fi

# --- 6. enable plugins in the .uproject -------------------------------------
log "Ensuring plugins are enabled in the .uproject …"
python3 - "$UPROJECT" <<'PY'
import json, sys
path = sys.argv[1]
with open(path) as f:
    data = json.load(f)
plugins = data.setdefault("Plugins", [])
names = {p.get("Name") for p in plugins}
for name in ("BeamPlatformNotifications", "BeamNotifTest"):
    if name not in names:
        plugins.append({"Name": name, "Enabled": True})
    else:
        for p in plugins:
            if p.get("Name") == name:
                p["Enabled"] = True
with open(path, "w") as f:
    json.dump(data, f, indent=2)
    f.write("\n")
print("  plugins ok")
PY

# --- 7. patch Config/DefaultEngine.ini --------------------------------------
log "Patching Config/DefaultEngine.ini (idempotent) …"
python3 - "$ENGINE_INI" <<'PY'
import sys
path = sys.argv[1]
with open(path) as f:
    text = f.read()

def ensure_block(text, marker, block):
    if marker in text:
        return text
    if not text.endswith("\n"):
        text += "\n"
    return text + "\n" + block.strip("\n") + "\n"

# Native-library settings (Android FCM toggle + deep-link scheme).
text = ensure_block(text, "[BeamableNotifications]", """
[BeamableNotifications]
; Set bUseFcm=True and add Build/Android/google-services.json to enable Android remote push.
bUseFcm=False
DeepLinkScheme=beamfarm
""")

# iOS: register the beamfarm:// URL scheme so OS deep links open the app.
# (The plugin UPL also injects this at package time; this keeps editor/runtime config in sync.)
ios_marker = "ADDITIONALPLISTDATA_BEAMNOTIF"
if ios_marker not in text:
    note = """
; BEAMNOTIF: BeamableNotifications appends a beamfarm:// CFBundleURLTypes entry via its iOS UPL
; (Plugins/BeamableNotifications/Source/BeamableNotifications/IOS/BeamableNotifications_UPL.xml).
; Remote push also needs "Enable Remote Notifications Support" + the App Group capability in Xcode.
; ADDITIONALPLISTDATA_BEAMNOTIF
"""
    if not text.endswith("\n"):
        text += "\n"
    text += note

with open(path, "w") as f:
    f.write(text)
print("  ini ok")
PY

# --- 8. summary -------------------------------------------------------------
cat <<EOF

$(log "Setup complete. Remaining manual / one-time steps:")
  1. Regenerate the BeamFarmMs Unreal client so Send/List push nodes exist:
       - Open the project in the Unreal Editor and run the Beamable CLI client generation,
         or run your usual 'beam' codegen for the BeamFarmMs microservice.
       - SendCampaignPushToSelf / ListMyDevices buttons auto-enable once the generated request
         headers appear (the test subsystem guards them with __has_include).
  2. Create the test level in-editor (one-time):
       - New Level 'L_NotificationTest' under Plugins/BeamNotifTest/Content/Levels.
       - World Settings → GameMode Override = BeamNotifTestGameMode.
       - Open that level (or set it as the editor/play map) to run the test screen.
  3. iOS only (Xcode, after packaging): enable "Remote Notifications Support",
       add the App Group 'group.com.beamable.notifications', and add a Notification Service
       Extension target from the staged BeamableNotificationServiceExtension/ sources.
  4. Android remote push (optional): set [BeamableNotifications] bUseFcm=True in
       DefaultEngine.ini and place google-services.json at Build/Android/.

  Build:  generate project files, then build the Editor target (or package for iOS/Android).
EOF
