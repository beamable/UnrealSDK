# Closed-app delivery analytics (Notification Service Extension)

The webhook that fires on push delivery **while the app is killed** is sent by an iOS
**Notification Service Extension (NSE)** — a tiny separate binary inside the app bundle
(`YourApp.app/PlugIns/…​.appex`). iOS launches it on every remote push carrying
`mutable-content:1` (which `BeamFarmMs.Apns.cs` already sends), even with no game code running.

UE/UPL can't create an iOS app-extension **target**, so `Scripts/add-nse.sh` builds a small
NSE and grafts it into the packaged build + re-signs.

## This NSE is self-contained — NO App Group needed

`add-nse.sh` generates a **minimal, self-contained** NSE that POSTs the webhook with the
endpoint **baked into its own Info.plist** (`BMNAnalyticsEndpoint`). It does NOT use an App
Group and does NOT link the Beamable core framework. That deliberately avoids the App Groups
requirement (explicit App IDs + capability + non-wildcard profiles) — App Groups can't be used
with an `iOS Team Provisioning Profile: *` wildcard profile, which is what automatic signing
uses here. The plain extension signs fine with the team's wildcard profile, no Apple-portal
setup required.

> Because of this, the App Group entitlement in `GameCenter.entitlements` must stay **commented
> out** — uncommenting it makes the *app itself* fail to sign on the wildcard profile
> ("provisioning profile doesn't support the App Groups capability"). The `ConfigureAnalytics`
> call / App Group sharing is only needed for the full-featured Beamable NSE (the staged
> `Extension/` sources), which is not what this script builds.

## Prereqs

- Xcode + automatic signing (team read from `[/Script/MacTargetPlatform.XcodeProjectSettings] CodeSigningTeam`).
- `sudo gem install xcodeproj` (used to generate the NSE Xcode project).
- The webhook endpoint comes from `[BeamPlatformNotifications] AnalyticsEndpoint` in `DefaultEngine.ini`
  (set during install); if blank the NSE installs but doesn't POST until you set one.

## Per build

Use the **"iOS + NSE → Device"** toolbar button (the `BeamPlatformNotificationsEditor` module). It
packages iOS, grafts + signs the NSE, and installs to the device you pick — streaming to the
Output Log (`LogBeamNotif`).

The bundled scripts can also be run by hand (they take the project context as args):

```
Plugins/BeamPlatformNotifications/Scripts/package-ios-deploy.sh \
   --project-dir <UnrealProjectDir> --device <UDID>
# or just the NSE step on an existing artifact:
Plugins/BeamPlatformNotifications/Scripts/add-nse.sh --app <path>.app --project-dir <UnrealProjectDir>
```

> Team + analytics endpoint are derived from the target project's `DefaultEngine.ini` (override with
> `--team` / `--endpoint`). Nothing project-specific is baked into the plugin.

## Verify

Register the device ("Send push to myself" needs the device registered first), then **fully
kill the app** and trigger a push — the webhook endpoint should receive a
`{"message":"📬 … delivered (app closed)"}` POST from the extension.

> Untested in this repo's CI — signed iOS packaging needs your device + account, so expect a
> round or two of iteration (the script prints `xcodebuild.log` on failure).

## Android counterpart — closed-app delivery handler

Android has no NSE; the equivalent closed-app reporting is a tiny native handler,
`com.beamable.unreal.BeamUnrealPushReceivedHandler`
(`Source/BeamPlatformNotifications/Android/java/…`). The APL compiles it into the app and
registers it via `<meta-data android:name="com.beamable.push.notification_received_handler">`, so
the Beamable Kotlin core invokes it **on push receipt even when the app is fully killed** (no Unreal
runtime running). It reads the **same** `[BeamPlatformNotifications] AnalyticsEndpoint` (injected
into the manifest as `com.beamable.analytics.endpoint`) and POSTs the same
`{"message":"📬 … delivered (app closed)"}` body. No extra setup — it ships and registers
automatically; if the endpoint is blank it stays dormant.

> FCM constraint: the killed-app handler fires for **local** notifications and for **data-only**,
> high-priority FCM messages. A message that carries a `notification` block is shown by the OS and
> only reaches the app on tap, so use data-only messages to exercise the closed-app path. (Remote
> push also requires `bUseFcm=True` + a staged `google-services.json`.)

## App-side delivery reporting (both platforms)

Local notifications never reach the closed-app handlers, so when `AnalyticsEndpoint` is set the
subsystem also POSTs from the running app on **foreground-present**, **tap**, and **cold-start**
(same one-`message`-field body). This is on automatically; opt out with
`[BeamPlatformNotifications] bAppSideAnalytics=False`. Each POST result is surfaced on the
`OnDeliveryReported(bSuccess, StatusCode, Label)` Blueprint event.
