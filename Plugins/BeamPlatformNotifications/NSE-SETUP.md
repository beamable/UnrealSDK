# Closed-app funnel analytics (Notification Service Extension)

The funnel **Received** event that fires on push delivery **while the app is killed** is emitted by
an iOS **Notification Service Extension (NSE)** — a tiny separate binary inside the app bundle
(`YourApp.app/PlugIns/…​.appex`). iOS launches it on every remote push carrying
`mutable-content:1` (which `BeamFarmMs.Apns.cs` already sends), even with no game code running.

UE/UPL can't create an iOS app-extension **target**, so `Scripts/add-nse.sh` builds a small
NSE and grafts it into the packaged build + re-signs.

## How the funnel NSE authenticates (App Group, not a webhook)

The full-featured Beamable NSE (the staged `Extension/` sources) does **not** POST to a configurable
webhook. It reads the player's persisted auth (bearer token + `cid`/`pid`/`host` realm routing) from
the **App Group** shared container — the same store the app writes via `ConfigureAuth` — and POSTs a
Beamable `CoreEvent` to `/report/custom_batch/{cid}/{pid}/{gamerTag}` for tracked campaign pushes
(`campaignId`+`nodeId`). If the authenticated POST can't finish within the NSE's ~30s budget it
persists the event to the App Group for replay on next app open. There is no `BMNAnalyticsEndpoint`
or `AnalyticsEndpoint` setting in this model.

> App Group note: linking the funnel NSE requires the App Group entitlement on both the app and the
> extension, which means explicit App IDs + the App Groups capability + non-wildcard provisioning
> profiles (it can't sign under an `iOS Team Provisioning Profile: *` wildcard). Set up the App Group
> in the Apple portal and reference it via `[/Script/BeamPlatformNotifications.Settings] AppGroup`.

> Legacy demo path: the inline NSE that `Scripts/add-nse.sh` currently generates is a **minimal,
> self-contained** stand-in (no App Group, no Beamable core link) kept only so it can sign under the
> wildcard profile with no Apple-portal setup. It predates the funnel and is being superseded by the
> staged funnel NSE above — see the `# TODO` note in `add-nse.sh`.

## Prereqs

- Xcode + automatic signing (team read from `[/Script/MacTargetPlatform.XcodeProjectSettings] CodeSigningTeam`).
- `sudo gem install xcodeproj` (used to generate the NSE Xcode project).
- The player auth that the funnel NSE POSTs with is supplied at runtime by the app via `ConfigureAuth`
  (persisted to the App Group); there is no endpoint to configure in `DefaultEngine.ini`.

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

> The signing team is derived from the target project's `DefaultEngine.ini` (override with `--team`).
> Nothing project-specific is baked into the plugin.

## Verify

Register the device ("Send push to myself" needs the device registered first), then **fully
kill the app** and trigger a tracked-campaign push — Beamable should record a **Received** funnel
event for that `campaignId`/`nodeId` (the NSE POSTs it to `/report/custom_batch`, or persists it for
replay on next app open if the NSE budget expires first).

> Untested in this repo's CI — signed iOS packaging needs your device + account, so expect a
> round or two of iteration (the script prints `xcodebuild.log` on failure).

## Android counterpart — closed-app funnel receipt

Android has no NSE; the equivalent closed-app reporting lives in the Beamable Kotlin core, which the
APL compiles into the app. On push receipt — **even when the app is fully killed** (no Unreal runtime
running) — the core emits the **Received** funnel event for tracked campaign pushes, authenticating
with the player token the app persisted via `ConfigureAuth` and POSTing the same Beamable `CoreEvent`
to `/report/custom_batch`. No webhook endpoint and no manifest `analytics.endpoint` are involved; it
ships and works automatically once `ConfigureAuth` has run at least once.

> FCM constraint: the killed-app path fires for **local** notifications and for **data-only**,
> high-priority FCM messages. A message that carries a `notification` block is shown by the OS and
> only reaches the app on tap, so use data-only messages to exercise the closed-app path. (Remote
> push also requires `bUseFcm=True` + a staged `google-services.json`.)

## Offer funnel events (both platforms)

Beyond the native Received/Opened stages, the app emits offer **Clicked**/**Converted** funnel events
via `TrackOfferClicked`/`TrackOfferConverted` (passing an `OfferTrackRequest`), attributed back to the
originating campaign. These go through the same authenticated `/report/custom_batch` POST.
