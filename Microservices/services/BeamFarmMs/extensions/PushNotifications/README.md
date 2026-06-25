# PushNotifications (Portal extension)

An admin Portal page for the **BeamFarmMs** microservice's push endpoints. It lists every
player who has registered a push device and lets you bulk-send a remote campaign push to any
selection of them.

## What it does

- **Registered players table** — calls `[ServerCallable] ListRegisteredPlayers` and shows
  each player's ID, device count, push platforms (`apns`/`fcm`), game platform/device, and
  last-updated time. Tick rows (or **Select all**) to choose recipients.
- **Send a notification** — bulk-sends via `[ServerCallable] SendCampaignPushToPlayer(playerId, PushCampaignRequest)`
  for each selected player and reports how many devices were delivered to. The request carries
  the optional §3.3 Notification Intent Data (campaign coordinates, repeatable offers, and a
  campaignData key→value map); when `campaignId` + `nodeId` are both set the microservice also
  emits a funnel **"Sent"** analytics event.

## How the roster is discovered

Device tokens live in a **private** per-player stat (`apns_devices`), and private stats can't be
enumerated across players. So the service also writes a **public** marker stat,
`push_devices` = device count, on every register/unregister/prune (see `BeamFarmMs.Push.cs` `SaveDevices`).
`ListRegisteredPlayers` finds the roster with `SearchStats("game","public","player", push_devices != 0)`
and then loads each player's private device summary. Tokens are never returned to the client.

## Run it

```bash
npm install
npm run dev          # vite dev server; load the extension in the Portal
# or, once the realm serves the portal-config endpoint:
beam project run --ids PushNotifications
beam portal open-extension PushNotifications
```

The microservice must be running (locally or deployed) for the calls to resolve. You'll need an
**admin** Portal session — both endpoints are `[ServerCallable]` and require the `*` (admin) scope.

## Note: hand-authored scaffold

This extension was created by hand rather than via `beam project new portal-extension` because that
command (and `portal extension list-extension-options` / `portal extension add-microservice`)
requires the realm's **remote portal-config** endpoint, which returns 404 on the current realm
(`api.beamable.com`, `DE_83112773772143616`). The CLI still **discovers** the extension by
convention (`beam project ps` lists it as a `portalExtension`), so this only affects scaffolding,
not use.

Consequences:
- `beamable/clients/BeamFarmMsClient.ts` + `beamable/clients/types/` are hand-written
  to mirror the generator's output (push endpoints only — BeamFarmMs also exposes gameplay
  endpoints this extension doesn't use). If the service's endpoint signatures change, re-run
  `beam portal extension add-microservice PushNotifications BeamFarmMs` (once the
  endpoint is reachable) to regenerate them.
- The mount config in `package.json` (`page`, `selector`) mirrors the working `SampleOneHealthCheck`
  example and was not validated against remote mount options.
