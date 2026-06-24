# Closed-app delivery analytics (Notification Service Extension)

The webhook that fires on push delivery **while the app is killed** is sent by an iOS
**Notification Service Extension (NSE)** — a tiny separate binary inside the app bundle
(`YourApp.app/PlugIns/…​.appex`). iOS launches it on every remote push carrying
`mutable-content:1` (which `BeamFarmMs.Apns.cs` already sends), even with no game code running.

UE/UPL can't create an iOS app-extension **target**, so `../../add-nse.sh` builds a small
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

- Xcode + your usual automatic signing (team `A6C4565DLF`).
- `sudo gem install xcodeproj` (used to generate the NSE Xcode project).
- The webhook endpoint comes from `[BeamableNotifications] AnalyticsEndpoint` in
  `DefaultEngine.ini` (defaults to the RN sample's Slack webhook); override with `--endpoint`.

## Per build

```
# Package Project (recommended): produces an .ipa, then graft + re-sign the NSE in:
./add-nse.sh --ipa "/path/to/BeamableUnrealIOS.ipa"
# install the resulting .ipa to the device (Xcode ▸ Devices, Apple Configurator, or devicectl)

# Launch On: the .app is built/signed/installed in one shot, so re-deploy after grafting:
./add-nse.sh --app "Binaries/IOS/BeamableUnrealIOS.app"
xcrun devicectl device install app --device <UDID> "Binaries/IOS/BeamableUnrealIOS.app"
```

> Launch On installs the *un-extended* app immediately, so you must re-install the grafted
> `.app`. Package Project is the cleaner flow for the NSE.

## Verify

Register the device ("Send push to myself" needs the device registered first), then **fully
kill the app** and trigger a push — the webhook endpoint should receive a
`{"message":"📬 … delivered (app closed)"}` POST from the extension.

> Untested in this repo's CI — signed iOS packaging needs your device + account, so expect a
> round or two of iteration (the script prints `xcodebuild.log` on failure).
