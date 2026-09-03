# BeamPlatformNotifications

A self-contained, reusable Unreal plugin wrapping the Beamable native notifications library for
**iOS and Android**: permissions, local + scheduled notifications, remote push (APNs/FCM),
notification callbacks/events, deep links, and closed-app delivery analytics.

## Modules
- **`BeamPlatformNotifications`** (Runtime) — `UBeamPlatformNotificationsSubsystem`
  (`UGameInstanceSubsystem`). iOS calls the Swift core's C ABI (`bmn_*`); Android calls the Kotlin
  core via JNI. No-op on editor/desktop so it always compiles. Blueprint-assignable delegates:
  `OnPermissionResult`, `OnTokenReceived/Error`, `OnNotificationPresented/Received/Tapped`,
  `OnPendingNotifications`, `OnDeliveryReceipts`, `OnDeepLink`. Funnel analytics:
  `ConfigureAuth`/`ClearAuth` (persist/clear the player bearer token for native funnel POSTs) and
  `TrackOfferClicked`/`TrackOfferConverted` (emit offer funnel events).
- **`BeamPlatformNotificationsEditor`** (Editor) — adds the **"iOS + NSE → Device"** toolbar
  button: pick a device, package iOS, graft + sign the closed-app Notification Service Extension,
  install. Runs as a child process streaming to the Output Log (`LogBeamNotif`); flips to Cancel
  while running.

## Install (into any UE project)
The installer ships in this folder (`install-beamplatformnotifications.sh`) — copy it into your UE
project (or run it in place) and point `--source` at your `nativeLibraries` checkout:
```
./install-beamplatformnotifications.sh --source <path/to/nativeLibraries>
```
Generates a self-contained copy (sources + the native binaries committed under `ThirdParty/` +
bundled `Scripts/`), installs it into the project, enables it, and **prompts** for the
project-specific values (App Group, deep-link scheme, FCM on/off) — writing them to
`DefaultEngine.ini`. Use `--generate-only <dir>` to just emit the plugin folder for sharing.
Nothing project-specific is baked into the plugin; everything is read from config at runtime/build
time.

> The binaries under `ThirdParty/` (iOS `BeamableNotifications.embeddedframework.zip`, Android
> `beamable-notifications-release.aar`) are staged by the repo's `dev-native.sh`. If `ThirdParty/`
> is empty, run `./dev-native.sh` from the repo root first (macOS + Xcode for the iOS framework).

## Funnel analytics
Campaign funnel events (Sent/Received/Opened/Clicked/Converted) are POSTed natively to Beamable.
The native code (iOS Swift core + NSE, Android Kotlin core + `BeamUnrealPushReceivedHandler`)
authenticates and POSTs even when the engine VM is asleep, using credentials the app supplies:
- **`ConfigureAuth(AuthJson)`** — persist the player bearer token + realm routing (`cid`/`pid`/
  `host`) so native funnel POSTs can authenticate. Call on login/refresh. **`ClearAuth()`** on logout.
- **`TrackOfferClicked(RequestJson)` / `TrackOfferConverted(RequestJson)`** — emit a Clicked /
  Converted funnel event for an in-app offer, attributed back to the originating campaign via the
  notification's intent data. `RequestJson` is the canonical `OfferTrackRequest`
  (`{campaignId,nodeId,gamerTag,accountId,cidPid,deeplink,offer:{...}}`).

Closed-app receipt funnel events are emitted natively: the **iOS** Notification Service Extension
(see `NSE-SETUP.md`) and the **Android** `BeamUnrealPushReceivedHandler` (registered via the APL).

## Settings (written to the project's `DefaultEngine.ini`)
- `[/Script/BeamPlatformNotifications.Settings] AppGroup` — iOS App Group id (UPL/Info.plist).
- `[BeamPlatformNotifications] DeepLinkScheme` — custom URL scheme (iOS `CFBundleURLSchemes` + Android VIEW intent).
- `[BeamPlatformNotifications] bUseFcm` — enable Android FCM remote push.

Funnel analytics needs no `DefaultEngine.ini` endpoint: the native layer authenticates with the
player bearer token supplied at runtime via `ConfigureAuth` and POSTs Beamable `CoreEvent`s
directly (see **Funnel analytics** above).

## Bundled scripts (`Scripts/`)
- `package-ios-deploy.sh` — package iOS → `add-nse.sh` → install to a device (driven by the button).
- `add-nse.sh` — build + graft + sign the closed-app Notification Service Extension.

See `NSE-SETUP.md` for the closed-app analytics extension details.
