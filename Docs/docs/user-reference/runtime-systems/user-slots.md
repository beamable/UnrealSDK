# User Slots

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