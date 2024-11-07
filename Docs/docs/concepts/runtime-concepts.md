<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Unreal SDK - Runtime Concepts
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

![InitFlow](../concepts/images/runtime-concepts-init-flow.png#center)

The next image shows a high-level description of the authentication flows supported by the SDK:


![](runtime-concept-authflow.png#center)

Now that you have a high-level understanding of the SDK's initialization flows, read up on how to achieve the two most common Sign Up and Login flows among the ones we provide.

## Player Sign Up and Login Flows with Beamable

The Beamable SDK comes with a set of pre-implemented operations for common sign-up use-cases. Here are how to set up a few of the common login/signup flows using Beamable.

!!! warning "Mobile and Console Support"
	 We DO NOT provide mobile support yet. This version of the SDK is focused on PC (Windows/Linux) and Dedicated Servers. Console and Mobile support will be added later.
### Login Flow - "Mobile Games" Style Authentication
Mobile games often want to create a **Guest Account** for the player so they can start playing quickly and later decide if they want to `Attach` that guest account to a more permanent identity.

The SDK supports this flow via the `UBeamRuntime::InitSDKWithFrictionlessLogin` function. Initializing the SDK with this function will immediately attempt to create a **Guest Account** at the `OwnerPlayerSlot` as soon as the SDK finishes initializing itself. If an account is already locally cached at that `FUserSlot` we'll login to that one automatically without making a request to Beamable.

The `On User Ready` callback provided to the `InitSDKWithFrictionlessLogin` function runs after the Guest Account was successfully created and, at that point, you can make further requests to Beamable. 

**Guest Accounts are lost if signed out (or have its locally cached data lost for any reason)**. To avoid that, players can to "attach" some persistent identity information to that guest account. `UBeamRuntime::Attach_____` do that. After a successful attach call, a player will be able to login via the corresponding `UBeamRuntime::Login____` operation. For example, if you `AttachEmailAndPassword` you'll be able to `LoginEmailAndPassword` to sign back into the account.

This user sign in flow does not run in Dedicated Servers even if `InitSDKWithFrictionlessLogin` is called. Dedicated Servers use a different form of authentication that is not based on `FUserSlots`.

### Login Flow - "PC/Console" Style Authentication
In PC/Console titles, often the user can sign-in and up from inside the game. That can happen either through an active form-filling process, an active request to third-party authentication (Discord, Google, etc...) or an automatic store-based login (Epic Online Services, PSN, Steam, etc...). 

***If your game has these flows, we recommend you use `InitSDK` and manage the login/signup flows in your game code instead. The steps below explain how to do that.***

In your `BeginPlay` implementation, call `UBeamRuntime::InitSDK`. It provides you different callbacks to handle initialization success or failure. At the end of a successful initialization, you can call `UBeamRuntime::SignUp____` or `UBeamRuntime::Login____` Operations with the appropriate parameters to login a user. 

You can react to the successful Login/SignUp either via registering a callback to `UBeamRuntime::OnUserReady` OR by the [operation's own events](../concepts/operations-and-waits.md).

We treat these operations as atomic inside the SDK and will clear any invalid partial state in case of any failure during their internal multi-step process; triggering `UBeamRuntime::OnUserReady` only in the case that the user is fully ready for use.

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

If the exposed hooks on these are not enough for your use case and constraints, as a user you can create your own `UBeamRuntimeSubsystem`. The SDK tries not to hide things from you so you can use the provided `UBeamRuntimeSubsystems` to understand how they are set up when creating your own. The documentation in [Lower-Level SDK Subsystems][#lower-level-sdk-subsystems] can also be useful when implementing your own `UBeamRuntimeSubsystems`. 

You can also opt out of these entirely by adding them to `UBeamCoreSettings` 's property: `ManuallyInitializedRuntimeSubsystems`. All subsystems in this list, and any other subsystem that depends on it, are not automatically initialized by the SDK. For example: adding `UBeamInventorySubsystem` to this list makes it so the SDK's default implementation of an inventory system will not be in-use until you manually initialize it. 

You can leverage the above to:

- Delay initialization of subsystems to a later point to reduce startup times.
- Remove our implementation of a set of systems so that you can use your own implementation of those systems.
- Disable systems that you do not want to use to reduce the SDK's request overhead.

Keep in mind that the simplest way is to build your features *on top of* these subsystems instead of replacing them. However, there are complex cases where it may be easier to make your own system *instead of* these subsystems. That's why we allow you to enable/disable systems with this granularity.

### Lower-Level SDK Subsystems
This section talks about lower-level details of how requests to Beamable get made. ***You don't need to read this***, but... you might want to if you plan on implementing your own `UBeamRuntimeSubsystem`. Here's why you'd want to do this:

- You want to replace one of our implementations with something quite custom and want to provide guarantees about your system's lifecycle that are similar to the ones we provide.
- You wish to guarantee that `On User Ready` has access to custom data fetched via Microservices and Microstorages.

We don't recommend writing your own unless you're confident you understand the topics below and are trying to solve one of the two problems listed above.

The lowest layer of systems are shared between the SDK's UE Editor integration and the SDK's Runtime integration:

- `UBeamUserSlots`: As explained at the start of this document, tracks multiple local signed-in users (for local co-op cases).

- `UBeam_____Api`:  Code-Generated Subsystems from our Backend OpenAPI spec.
	- These are stateless subsystems.
	- These provides you low-level access to every end-point of our backend even if we don't have utilities in the SDK that do exactly what you want.
	- As UE doesn't allow for namespaces AND BP-compatibility, this is verbose. We recommend more liberal use of `auto` when dealing with Code-Gen API Types.

- `UBeamBackend`: Contains BP-Compatible and Lambda compatible implementations of Request/Response handling functions. It handles:
	- Request/Response serialization and deserialization.
	- Configurable Retry Logic. Request, User and call-site granularity.
	- Transparent and Automatic Re-Auth in case of expired `AccessToken` through a user's `RefreshToken`.
	- `LogBeamBackend Verbose` also is a useful diagnostic tool as it will print out the entire process of building the request, sending it out and receiving its response.
	
- `UBeamNotifications` and `UBeam_____Notifications`: Leverages UE's WebSocket implementation and associates different web-socket connections with different user slots. 
	- `UBeam_____Notifications` are implemented per Beamable backend system (inventory, stats, etc...) to expose two UE function versions, one BP-Compatible and the other Lambda-Compatible, that register a handler to process a specific type of notification.
	- These are used by `UBeamRuntimeSubsystem` based on their semantic needs. For example, `UBeamMatchmakingNotifications` subscribes to notifications for the matchmaking ticket while a UserSlot is on a given queue. 
	- You can use Microservices to send out custom notifications --- those can be received in clients by creating your own subsystem modeled after these.

- `UBeamRequestTracker`: A BP-compatible implementation of Async Operations that can emit various Events as it goes along --- you can think of these as "BP-Compatible Promises".
	- These are integrated with our `UBeam____Api` subsystems. 
	- `BeginOperation` is effectively the same a creating a new promise. 
	- `TriggerOperationSuccess`, `TriggerOperationError` and `TriggerOperationCancelled` should be called when you want to complete the Operation.
	- This is a somewhat complex subsystem so we recommend you read [Operations & Waits](../operations-and-waits).

The systems above are used by various environments the Beamable SDK runs in: PIE, Editor, Dedicated Server Builds and regular game builds. Their code is pretty heavily commented; so, feel free to read it and figure things out that way.

#### Docs: C++ version of Blueprint examples
Most of our docs contains examples using Blueprints. Unless described otherwise there is option to achieve same results in C++ while following Blueprint sample. In C++, the subsystems and function names are the same except that, for lambda-binding, you'll need to use the `CPP_` versions of functions.
