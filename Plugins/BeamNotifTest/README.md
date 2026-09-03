# BeamNotifTest

A **standalone** test harness for the `BeamPlatformNotifications` native library (iOS + Android),
mirroring the React Native sample. It is fully isolated from the BeamFarm game — it depends
only on `BeamableCore`, `BeamableUnrealMicroserviceClients`, and `BeamPlatformNotifications`, and
runs in its own level so you can build/test it without touching the main game.

## What it exercises

The UI (`UBeamNotifTestWidget`, built entirely in C++ — no `.uasset` needed) has:

- **Beamable** — Connect (frictionless/guest login on the `Player0` slot) + status.
- **Notifications (native)** — request permission, fire immediate (#777) and delayed (#888)
  local notifications, register for remote push (APNs/FCM), cancel all.
- **Remote push (BeamFarmMs microservice)** — register this device's token, send-push-to-self,
  list my devices. *(Send/List auto-enable once the BeamFarmMs client is regenerated — see below.)*
- **Deep links** — fire a notification carrying `beamfarm://details/123`, or navigate directly.
  Both notification-tap deep links and OS URL-scheme deep links route to an in-screen
  "Details" panel via the subsystem's `OnDeepLink` event.
- **Activity log** — timestamped, mirrors the RN app's log.

## Architecture

| Piece | Role |
|-------|------|
| `UBeamPlatformNotificationsSubsystem` (in the `BeamPlatformNotifications` plugin) | The native bridge. iOS → Swift C ABI (`bmn_*`); Android → Kotlin via JNI (`UnrealPush`/`UnrealDeepLink` + `Java_..._native*` exports). No-op in editor/desktop. |
| `UBeamNotifTestSubsystem` | Beam connect + `BeamFarmMs` push calls (modeled on `UBeamFarmSubsystem`). |
| `ABeamNotifTestGameMode` / `ABeamNotifTestPlayerController` | Spawn the widget onto the viewport. No pawn. |
| `UBeamNotifTestWidget` | The code-built UMG screen; binds subsystem delegates. |

## Running it

1. Install the `BeamPlatformNotifications` plugin once:
   `../../install-beamplatformnotifications.sh --source <path/to/nativeLibraries>` (stages native
   binaries, enables the plugin, prompts for project values, patches config).
2. Build the editor target.
3. Create a level **once** in-editor: `Content/Levels/L_NotificationTest`, set
   **World Settings → GameMode Override = `BeamNotifTestGameMode`**, then open/play it.
4. In the editor the native calls are no-ops (logged); deploy to an iOS/Android device to
   exercise real notifications and push.

## Editor button: package iOS + NSE → device (one click)

The **"iOS + NSE → Device"** toolbar button is provided by the `BeamPlatformNotifications` plugin
(its `BeamPlatformNotificationsEditor` module) — not this sample. Click it to: pick a connected
device, package iOS (`RunUAT BuildCookRun`), embed + sign the closed-app Notification Service
Extension, and install to the device. It runs as a **child process of the editor and streams to
the Output Log** (`LogBeamNotif`); the button flips to **Cancel** while running. macOS only; needs
`sudo gem install xcodeproj` for the NSE step. The scripts live in
`Plugins/BeamPlatformNotifications/Scripts/`; see `Plugins/BeamPlatformNotifications/NSE-SETUP.md`.

## Enabling Send / List push (microservice)

The `BeamFarmMs` C# service exposes `ListMyDevices` and `SendCampaignPushToSelf` as
`[ClientCallable]`, but the Unreal client must be regenerated to get the C++ nodes. After
regenerating (Beamable CLI / editor codegen for `BeamFarmMs`), the generated request headers
appear and `UBeamNotifTestSubsystem` auto-enables those calls (guarded with `__has_include`).
The subsystem's own `SendPushToSelf(Title, Body, DeepLink)` wrapper builds an (untracked)
`UPushCampaignRequestBody` and calls `SendCampaignPushToSelf` under the hood.

## On-device notes

- **iOS**: enable "Remote Notifications Support", add the App Group
  `group.com.beamable.notifications`, and add a Notification Service Extension target from the
  staged `BeamableNotificationServiceExtension/` sources (see `docs/unreal.md` in the native lib).
- **Android**: set `[BeamPlatformNotifications] bUseFcm=True` in `DefaultEngine.ini` and add
  `Build/Android/google-services.json` for FCM. Local notifications + deep links work without it.
  Test a URL deep link with:
  `adb shell am start -W -a android.intent.action.VIEW -d "beamfarm://details/123" com.beamable.samples.beamfarm`
