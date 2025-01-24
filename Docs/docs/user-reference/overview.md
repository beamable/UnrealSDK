# SDK Technical Overview
The Beamable SDK is a collection of custom UE `Engine`, `Editor` and `GameInstance` Subsystems. **Game-Maker Code** (as in, code the Beamable customer writes) can take advantage of various guarantees we provide by understanding how these subsystems work.
## `UBeamUserSlots` and `FUserSlot`
The concept of a `UserSlot` represents a named "local player" slot. By default, we ship with two lists of User Slots inside the `UBeamCoreSettings`(found in `Project Settings -> Engine`) :

- The `RuntimeUserSlots` , that contains a default slot at index 0, called `Player0`. 
	- The first index of this list is referred to as the `OwnerPlayerSlot`.
	- This list is the list of expected player slots for every running client of your game.
	- If you're game does not need multiple users logged into the same game-client, you don't need multiple slots.
- The `EditorUserSlots`, that contains a default slot at index 0, called `MainEditorDeveloperSlot`. 
	- The Beamable Editor integration also uses the user slot system to authenticate the requests it makes to the Beamable servers. So... when you signed into the editor, you're data is associated to this default slot.

The `UBeamUserSlots` Engine Subsystem is responsible for:

- Enabling local co-op games to have multiple players logged in at the same time.
- Name-spacing slots to support Multiplayer PIE-mode. 
	- This is why, like UE, we take in a `UObject* CallingContext` in certain parts of our APIs.
- Assert that only slots defined in the `UBeamCoreSettings` are in use. 
	- Any User Slot with `Test` in its name is exempt from this rule so you can write automated tests with arbitrary amounts of user slots by using user slots with `Test` in their names.

***This subsystem does not handle the actual logging in and logging out.*** That is handled by two other Subsystems:

- `UBeamRuntime` , a `GameInstanceSubsystem`, is responsible for PIE instances and packaged games. 
- `UBeamEditor`, an `EditorSubsystem`, is responsible for the Editor integration.

### `UBeamRuntime` & `UBeamRuntimeSubsystem`
`UBeamRuntime` is the entry point for the Beamable SDK at runtime (PIE, packaged game clients and dedicated servers). It is a `GameInstanceSubsystem` and follows its lifecycle rules. It is responsible for a couple of things:

- It controls the SDK's runtime initialization flow.
- It controls the various SDK's user \[un\]-authentication flows.
- It controls `UBeamRuntimeSubsystems'` lifecycle with respect to the SDK itself and `FUserSlots`.

The image below describes how the SDK's lifecycle injects itself into UE's lifecycle:

![runtime-concepts-init-flow.png](../media/imgs/runtime-concepts-init-flow.png)
The next image shows a high-level description of the authentication flows supported by the SDK:

![runtime-concept-authflow.png](../media/imgs/runtime-concept-authflow.png)
Now that you have a high-level understanding of the SDK's initialization flows, read up on how to achieve the two most common Sign Up and Login flows among the ones we provide.

### Understanding `BeamRuntimeSubsystems`
`BeamRuntimeSubsystems` are stateful subsystems that provide some specific Beamable functionality. They are built on top of our Auto Generated `UBeam____Api` classses to make it simpler to leverage our APIs; that way:

1. You don't have to set up the common case.
2. You can use them and their extension points for variations of the common case.
3. You can use them as reference implementations to implement your own custom use cases outside of the common case.

These are hand-written. Here's a few examples of existing ones:

- `UBeamContentSubsystem`: This leverages the Beamable Content system to receive dynamic updates to read-only game data definition; also supports baked in-build content through the same API.
- `UBeamInventorySubsystem`: This provides builder functions around our Inventory APIs that allows you to combine what would be multiple API requests into a single batched inventory update. It also receives inventory notifications coming from the server and keeps those in sync.
- `UBeamMatchmakingSubsystem`: This provides you a stateful way of joining/canceling a matchmaking queue and receiving updates when a match is found.

These systems make use of the various `UBeamRuntime::____` callbacks to keep their state correct and expose callbacks and configuration options for **Game-Maker Code** to run with semantically relevant guarantees.

If the exposed hooks on these are not enough for your use case and constraints, as a user you can create your own `UBeamRuntimeSubsystem`. The SDK tries not to hide things from you so you can use the provided `UBeamRuntimeSubsystems` to understand how they are set up when creating your own. The documentation in [Lower Level SDK](runtime-systems/lower-level.md) can also be useful when implementing your own `UBeamRuntimeSubsystems`. 

You can also opt out of these entirely by adding them to `UBeamCoreSettings` 's property: `ManuallyInitializedRuntimeSubsystems`. All subsystems in this list, and any other subsystem that depends on it, are not automatically initialized by the SDK. For example: adding `UBeamInventorySubsystem` to this list makes it so the SDK's default implementation of an inventory system will not be in-use until you manually initialize it. 

You can leverage the above to:

- Delay initialization of subsystems to a later point to reduce startup times.
- Remove our implementation of a set of systems so that you can use your own implementation of those systems.
- Disable systems that you do not want to use to reduce the SDK's request overhead.

Keep in mind that the simplest way is to build your features *on top of* these subsystems instead of replacing them. However, there are complex cases where it may be easier to make your own system *instead of* these subsystems. That's why we allow you to enable/disable systems with this granularity.
