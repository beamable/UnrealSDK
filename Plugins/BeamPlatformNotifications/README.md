# BeamPlatformNotifications

A self-contained, reusable Unreal plugin wrapping the Beamable native notifications library for
**iOS and Android**: permissions, local + scheduled notifications, remote push (APNs/FCM),
notification callbacks/events, deep links, and closed-app delivery analytics.

## Modules
- **`BeamPlatformNotifications`** (Runtime) — `UBeamPlatformNotificationsSubsystem`
  (`UGameInstanceSubsystem`). iOS calls the Swift core's C ABI (`bmn_*`); Android calls the Kotlin
  core via JNI. No-op on editor/desktop so it always compiles. Blueprint-assignable delegates:
  `OnPermissionResult`, `OnTokenReceived/Error`, `OnNotificationPresented/Received/Tapped`,
  `OnPendingNotifications`, `OnDeliveryReceipts`, `OnDeepLink`.
- **`BeamPlatformNotificationsEditor`** (Editor) — adds the **"iOS + NSE → Device"** toolbar
  button: pick a device, package iOS, graft + sign the closed-app Notification Service Extension,
  install. Runs as a child process streaming to the Output Log (`LogBeamNotif`); flips to Cancel
  while running.

## Install (into any UE project)
```
./install-beamplatformnotifications.sh --source <path/to/nativeLibraries>
```
Generates a self-contained copy (sources + staged native binaries + bundled `Scripts/`), installs
it into the project, enables it, and **prompts** for the project-specific values (App Group,
deep-link scheme, analytics endpoint, FCM on/off) — writing them to `DefaultEngine.ini`. Use
`--generate-only <dir>` to just emit the plugin folder for sharing. Nothing project-specific is
baked into the plugin; everything is read from config at runtime/build time.

## Settings (written to the project's `DefaultEngine.ini`)
- `[/Script/BeamPlatformNotifications.Settings] AppGroup` — iOS App Group id (UPL/Info.plist).
- `[BeamPlatformNotifications] DeepLinkScheme` — custom URL scheme (iOS `CFBundleURLSchemes` + Android VIEW intent).
- `[BeamPlatformNotifications] AnalyticsEndpoint` — closed-app delivery webhook (NSE).
- `[BeamPlatformNotifications] bUseFcm` — enable Android FCM remote push.

## Bundled scripts (`Scripts/`)
- `package-ios-deploy.sh` — package iOS → `add-nse.sh` → install to a device (driven by the button).
- `add-nse.sh` — build + graft + sign the closed-app Notification Service Extension.

See `NSE-SETUP.md` for the closed-app analytics extension details.
