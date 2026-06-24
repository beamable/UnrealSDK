#!/usr/bin/env bash
#
# add-nse.sh — embed a self-contained Notification Service Extension (NSE) into a packaged
# iOS build so a delivery webhook fires even when the app is KILLED (closed-app analytics,
# matching the React Native sample).
#
# This NSE is intentionally minimal and SELF-CONTAINED:
#   * no `import BeamableNotifications` (no core framework to link), and
#   * NO App Group — the webhook endpoint is baked into the extension's own Info.plist.
# That avoids the App Groups requirement (explicit App IDs + capability + non-wildcard
# profiles) that fails under an "iOS Team Provisioning Profile: *" wildcard profile.
# It signs cleanly with automatic (Xcode-managed) signing using the team's wildcard profile.
#
# Works for "Launch On" (a .app on disk) and "Package Project" (an .ipa).
#
# Usage:
#   ./add-nse.sh --app <path>.app --project-dir <UnrealProjectDir>   # Launch On
#   ./add-nse.sh --ipa <path>.ipa --project-dir <UnrealProjectDir>   # Package Project
# Options (all derived from the target project's DefaultEngine.ini when omitted):
#   --project-dir <dir>  Unreal project root (used to read team + endpoint from config)
#   --team <ID>          signing team (default: [/Script/MacTargetPlatform.XcodeProjectSettings] CodeSigningTeam)
#   --endpoint <url>     analytics webhook (default: [BeamPlatformNotifications] AnalyticsEndpoint)
#
set -euo pipefail

PROJECT_DIR=""
TEAM=""
ENDPOINT=""
APP=""
IPA=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --app) APP="$2"; shift 2 ;;
    --ipa) IPA="$2"; shift 2 ;;
    --team) TEAM="$2"; shift 2 ;;
    --endpoint) ENDPOINT="$2"; shift 2 ;;
    --project-dir) PROJECT_DIR="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 1 ;;
  esac
done

log()  { printf '\033[0;36m[nse]\033[0m %s\n' "$*"; }
warn() { printf '\033[0;33m[warn]\033[0m %s\n' "$*"; }
die()  { printf '\033[0;31m[err]\033[0m %s\n' "$*" >&2; exit 1; }

[[ -n "$APP" || -n "$IPA" ]] || die "Pass --app <path.app> or --ipa <path.ipa>."

INI="$PROJECT_DIR/Config/DefaultEngine.ini"
ini_val() { grep -E "^\s*$1=" "$INI" 2>/dev/null | head -1 | sed 's/^[^=]*=//' | tr -d '\r'; }

# Derive project-specific values from the target project's config (flags override).
[[ -z "$ENDPOINT" && -f "$INI" ]] && ENDPOINT="$(ini_val AnalyticsEndpoint)"
[[ -z "$TEAM"     && -f "$INI" ]] && TEAM="$(ini_val CodeSigningTeam)"
[[ -n "$ENDPOINT" ]] || warn "No AnalyticsEndpoint configured ([BeamPlatformNotifications]) — the NSE will be installed but won't POST until one is set."
[[ -n "$TEAM" ]] || warn "No signing team resolved (CodeSigningTeam) — pass --team <ID> if the appex build fails to sign."

command -v xcodebuild >/dev/null || die "xcodebuild not found (install Xcode)."
( command -v gem >/dev/null && gem list -i xcodeproj >/dev/null 2>&1 ) || \
  die "Ruby 'xcodeproj' gem required. Install with: sudo gem install xcodeproj"

log "Webhook endpoint: $ENDPOINT"

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

# ── 1. Self-contained NSE source (no core dependency, no App Group) ──────────
cat > "$WORK/NotificationService.swift" <<'SWIFT'
import UserNotifications
import Foundation

/// Minimal closed-app delivery reporter. iOS runs this on every remote push carrying
/// `mutable-content:1` — even when the app is terminated — and POSTs a webhook before
/// delivering the notification. The endpoint is read from this extension's own Info.plist
/// (BMNAnalyticsEndpoint), so no App Group / shared container is needed.
final class NotificationService: UNNotificationServiceExtension {
    private var contentHandler: ((UNNotificationContent) -> Void)?
    private var bestAttempt: UNMutableNotificationContent?

    override func didReceive(_ request: UNNotificationRequest,
                             withContentHandler handler: @escaping (UNNotificationContent) -> Void) {
        contentHandler = handler
        let content = (request.content.mutableCopy() as? UNMutableNotificationContent) ?? UNMutableNotificationContent()
        bestAttempt = content

        guard let endpoint = Bundle.main.object(forInfoDictionaryKey: "BMNAnalyticsEndpoint") as? String,
              !endpoint.isEmpty, let url = URL(string: endpoint) else {
            handler(content); return
        }

        let title = content.title.isEmpty ? "Beamable notification" : content.title
        let body: [String: Any] = ["message": "📬 \(title) delivered (app closed)"]

        var req = URLRequest(url: url)
        req.httpMethod = "POST"
        req.setValue("application/json", forHTTPHeaderField: "Content-Type")
        req.httpBody = try? JSONSerialization.data(withJSONObject: body)

        URLSession.shared.dataTask(with: req) { _, _, _ in handler(content) }.resume()
        // Safety net: deliver before iOS reclaims the extension if the POST stalls.
        DispatchQueue.global().asyncAfter(deadline: .now() + 25) { [weak self] in
            if let c = self?.bestAttempt { self?.contentHandler?(c); self?.bestAttempt = nil }
        }
    }

    override func serviceExtensionTimeWillExpire() {
        if let c = bestAttempt { contentHandler?(c) }
    }
}
SWIFT

# ── 2. NSE Info.plist (endpoint baked in; no entitlements file) ──────────────
cat > "$WORK/Info.plist" <<PLIST
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0"><dict>
  <key>CFBundleDisplayName</key><string>BeamableNotificationServiceExtension</string>
  <key>CFBundleExecutable</key><string>\$(EXECUTABLE_NAME)</string>
  <key>CFBundleIdentifier</key><string>\$(PRODUCT_BUNDLE_IDENTIFIER)</string>
  <key>CFBundleName</key><string>\$(PRODUCT_NAME)</string>
  <key>CFBundlePackageType</key><string>\$(PRODUCT_BUNDLE_PACKAGE_TYPE)</string>
  <key>CFBundleShortVersionString</key><string>1.0</string>
  <key>CFBundleVersion</key><string>1</string>
  <key>BMNAnalyticsEndpoint</key><string>$ENDPOINT</string>
  <key>NSExtension</key><dict>
    <key>NSExtensionPointIdentifier</key><string>com.apple.usernotifications.service</string>
    <key>NSExtensionPrincipalClass</key><string>\$(PRODUCT_MODULE_NAME).NotificationService</string>
  </dict>
</dict></plist>
PLIST

# ── 3. Generate a one-target Xcode project and build a signed .appex ─────────
cat > "$WORK/gen.rb" <<'RUBY'
require 'xcodeproj'
work = ENV['WORK']; team = ENV['TEAM']
proj = Xcodeproj::Project.new(File.join(work, 'BeamableNSE.xcodeproj'))
t = proj.new_target(:app_extension, 'BeamableNotificationServiceExtension', :ios, '14.0')
group = proj.new_group('Sources')
t.add_file_references([group.new_file(File.join(work, 'NotificationService.swift'))])
t.build_configurations.each do |c|
  s = c.build_settings
  s['PRODUCT_BUNDLE_IDENTIFIER']  = ENV['NSE_BUNDLE_ID']
  s['INFOPLIST_FILE']             = File.join(work, 'Info.plist')
  s['CODE_SIGN_STYLE']            = 'Automatic'
  s['DEVELOPMENT_TEAM']           = team
  s['SWIFT_VERSION']              = '5.0'
  s['IPHONEOS_DEPLOYMENT_TARGET'] = '14.0'
  s['TARGETED_DEVICE_FAMILY']     = '1,2'
  s['GENERATE_INFOPLIST_FILE']    = 'NO'
  s['SKIP_INSTALL']               = 'NO'
end
proj.save
RUBY

resolve_bundle_id() { /usr/libexec/PlistBuddy -c "Print :CFBundleIdentifier" "$1/Info.plist"; }

embed_into_app() {
  local appdir="$1"
  local appid nseid
  appid="$(resolve_bundle_id "$appdir")"
  nseid="$appid.NSE"   # short, wildcard-friendly suffix; no explicit App ID needed
  log "App: $appid → NSE: $nseid"

  if [[ ! -d "$WORK/dd/Build/Products" ]]; then
    WORK="$WORK" TEAM="$TEAM" NSE_BUNDLE_ID="$nseid" ruby "$WORK/gen.rb"
    log "Building signed .appex (xcodebuild, automatic signing)..."
    xcodebuild -project "$WORK/BeamableNSE.xcodeproj" \
      -scheme BeamableNotificationServiceExtension -configuration Release \
      -sdk iphoneos -derivedDataPath "$WORK/dd" -allowProvisioningUpdates \
      build >"$WORK/xcodebuild.log" 2>&1 || { tail -50 "$WORK/xcodebuild.log"; die "appex build failed"; }
  fi
  local appex; appex="$(find "$WORK/dd/Build/Products" -name '*.appex' | head -1)"
  [[ -d "$appex" ]] || die "built .appex not found"

  log "Embedding $(basename "$appex") into $appdir/PlugIns/"
  mkdir -p "$appdir/PlugIns"
  rm -rf "$appdir/PlugIns/$(basename "$appex")"
  cp -R "$appex" "$appdir/PlugIns/"

  local idhash; idhash="$(security find-identity -v -p codesigning | awk '/Apple Develop/{print $2; exit}')"
  [[ -n "$idhash" ]] || die "no 'Apple Development' codesigning identity in keychain"

  log "Signing embedded extension + re-sealing app..."
  codesign -f --timestamp=none --generate-entitlement-der -s "$idhash" "$appdir/PlugIns/$(basename "$appex")"
  # Re-seal the app with its own existing entitlements (unchanged — no App Group needed).
  codesign -d --entitlements - --xml "$appdir" > "$WORK/app.entitlements" 2>/dev/null || true
  if [[ -s "$WORK/app.entitlements" ]]; then
    codesign -f --timestamp=none --generate-entitlement-der --entitlements "$WORK/app.entitlements" -s "$idhash" "$appdir"
  else
    codesign -f --timestamp=none -s "$idhash" "$appdir"
  fi
  codesign --verify --deep --strict "$appdir" && log "Signature verified."
}

# ── 4. Drive for .app or .ipa ───────────────────────────────────────────────
if [[ -n "$APP" ]]; then
  [[ -d "$APP" ]] || die "app not found: $APP"
  embed_into_app "$APP"
  log "Done. Launch-On .app now contains the NSE (re-install it to the device to use)."
fi

if [[ -n "$IPA" ]]; then
  [[ -f "$IPA" ]] || die "ipa not found: $IPA"
  log "Unpacking $IPA..."
  rm -rf "$WORK/ipa"; mkdir -p "$WORK/ipa"
  ( cd "$WORK/ipa" && unzip -q "$IPA" )
  appinipa="$(find "$WORK/ipa/Payload" -maxdepth 1 -name '*.app' | head -1)"
  [[ -d "$appinipa" ]] || die "no .app inside the ipa Payload"
  embed_into_app "$appinipa"
  log "Repacking .ipa..."
  ( cd "$WORK/ipa" && zip -qr "$IPA.withnse" Payload )
  mv "$IPA.withnse.zip" "$IPA" 2>/dev/null || mv "$IPA.withnse" "$IPA"
  log "Done. $IPA now contains the NSE."
fi
