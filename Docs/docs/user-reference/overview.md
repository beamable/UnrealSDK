# SDK Technical Overview
The Beamable SDK is a collection of custom UE `Engine`, `Editor` and `GameInstance` Subsystems.
**Game-Maker Code** (as in, code the Beamable customer writes) can take advantage of various guarantees we provide by understanding how these subsystems work.

The SDK's Plugin is divided into several modules:

- **BeamableCore** contains the `UEngineSubsystem` implementations shared between `Editor` and `Runtime` executing environments. 
It also contains the `UBeamContentObject` schema definitions for our [content system](beamable-services/content.md).
- **BeamableCoreRuntime** contains the `UBeamRuntime` and `UBeamRuntimeSubsystem` implementations and manage the SDK lifecycle at runtime.
- **BeamableCoreEditor** and **BeamableCoreRuntimeEditor** contains `UBeamEditor` and our editor integration code: custom BlueprintNodes, PropertyCustomizations, etc...

For any technical lead (making system-level decisions), effective use of Beamable and the Unreal SDK requires you to understand a few core concepts.
So, after reading this document, you'll want to start here:

- [**Content**](beamable-services/content.md) is how you define your game's configuration --- balancing data, currency and item definitions, etc... Most of our systems depend on Content so, its a good place to start.
- [**Identity**](beamable-services/identity.md) the various ways you can manage a player's account and login flows.
- [**Microservices**](microservices/microservices.md) are our version of cloud-code --- but also much more.
- [**Federation**](federation/federation.md) are effectively exposed hooks in our backend's various features that you can hook into with custom behavior. You can leverage this for integrating with third-party authentication, initial player state and a lot more. 

Aside from those core concepts, the links below explain some of our higher-level systems.

- [**Stats**](beamable-services/stats.md) and [**Inventory**](beamable-services/inventory.md) are our general-case player-data stores. You can use these to store player-related data and implement a variety of features with them.
- [**Matchmaking**](beamable-services/matchmaking.md) and [**Lobbies**](beamable-services/lobbies.md) are part of our suite of services for real-time multiplayer games.
- [**Stores**](beamable-services/stores.md) and [Announcements](beamable-services/announcements.md) are part of our suite of services to help with live-ops meta-game engagement.


## SDK's Runtime (`UBeamRuntime` & `UBeamRuntimeSubsystem`)
`UBeamRuntime` is the entry point for the Beamable SDK at runtime (PIE, packaged game clients and dedicated servers).
It is a `GameInstanceSubsystem` and follows its lifecycle rules. 
It is responsible for a couple of things:

- It controls the SDK's runtime initialization flow.
- It controls the various SDK's user \[un\]-authentication flows.
- It controls `UBeamRuntimeSubsystems'` lifecycle with respect to the SDK's initialization flow itself and `FUserSlot` authentication.

The image below describes how the SDK's lifecycle injects itself into UE's lifecycle:

![runtime-concepts-init-flow.png](../media/imgs/runtime-concepts-init-flow.png)

The next image shows a high-level description of the authentication flows supported by the SDK:

![runtime-concept-authflow.png](../media/imgs/runtime-concept-authflow.png)

## Understanding `BeamRuntimeSubsystems`
`BeamRuntimeSubsystems` are stateful subsystems that provide some specific Beamable functionality. 
They are built on top of our auto-generated `UBeam____Api` classes to make it simpler to leverage our APIs; that way:

1. You don't have to set up the common case.
2. You can use them and their extension points for variations of the common case.
3. You can use them as reference implementations to implement your own custom use cases.

These are handwritten. Here's a few examples:

- `UBeamStatsSubsystem`: This enables you to store arbitrary key-value pairs associated to a player's account.
- `UBeamInventorySubsystem`: This provides builder functions around our Inventory APIs that allows you to combine what would be multiple API requests into a single batched inventory update. It also receives inventory notifications coming from the server and keeps those in sync.
- `UBeamMatchmakingSubsystem`: This provides you a stateful way of joining/canceling a matchmaking queue and receiving updates when a match is found.

These systems make use of the various `UBeamRuntime::____` callbacks to keep their state correct and expose callbacks and configuration options for **Game-Maker Code** to run with semantically relevant guarantees.

If the exposed hooks on these are not enough for your use case and constraints, as a user you can create your own `UBeamRuntimeSubsystem`. 
The SDK does not obfuscate its inner-workings from you so you can use the existing `UBeamRuntimeSubsystems` as a reference to understand how to create your own.
The documentation in [Lower Level SDK](runtime-systems/lower-level.md) and [Operations & Waits](runtime-systems/operations-and-waits.md) can also be useful when implementing your own `UBeamRuntimeSubsystems`. 

You can also opt out of these entirely by adding them to `UBeamCoreSettings` 's property: `ManuallyInitializedRuntimeSubsystems`.
All subsystems in this list, and any other subsystem that depends on it, are not automatically initialized by the SDK.
For example, if `UBeamInventorySubsystem` is in this list, this system will not be usable until you manually initialize it. 

You can leverage the above to:

- Delay initialization of subsystems to a later point to reduce startup times.
- Remove our implementation of a set of systems so that you can use your own implementation of those systems without paying the overhead of our default implementations.
- Disable systems that you do not want to use to reduce the SDK's request overhead.

Keep in mind that the simplest way is to build your features *on top of* these subsystems instead of replacing them.
However, there are complex cases where it may be easier to make your own system *instead of* these subsystems. 
That's why we allow you to enable/disable systems with this granularity.
