# Lower-Level SDK Subsystems

This section talks about lower-level details of how requests to Beamable get made. 
***You don't need to read this***, but... you might want to if you plan on implementing your own `UBeamRuntimeSubsystem`. 
Here's why you'd want to do this:

- You want to replace one of our implementations with something custom and want to provide guarantees about your system's lifecycle that are similar to the ones we provide.
- You wish to guarantee that when `UBeamRuntime::OnUserReady` is triggered, you'll already have access to custom data fetched via Microservices and MicroStorages.

We don't recommend writing your own unless you're confident you understand the topics below and are trying to solve one of the two problems listed above.

!!! warning "Low Level Usage"
    The systems described here are used by various environments the Beamable SDK runs in: PIE, Editor, Dedicated Server Builds and regular game builds. 
    Their code is pretty heavily commented; so, feel free to read it and figure things out that way.

The lowest layer of systems are shared between the SDK's UE Editor integration and the SDK's Runtime integration:

- `UBeamUserSlots`: As explained at the start of this document, tracks multiple local signed-in users (for local co-op cases).
    - Take a look at [User Slots](user-slots.md) for more information about these.
   
- `UBeamRequestTracker`: Provides BP-compatible async operations that emit various events as it goes along.
    - You can think of these as "BP-Compatible Promises".
    - These are integrated with our `UBeam____Api` subsystems.
    - `BeginOperation` is effectively the same a creating a new promise.
    - `TriggerOperationSuccess`, `TriggerOperationError` and `TriggerOperationCancelled` should be called when you want to complete the Operation.
    - This is a somewhat complex subsystem so we recommend you read [Operations and Waits](operations-and-waits.md)

- `UBeam_____Api`:  Code-Generated Subsystems from our Backend OpenAPI spec.
    - These are stateless `UEngineSubsystem` implementations.
    - These provide you low-level access to every end-point of our backend even if we don't have utilities in the SDK that do exactly what you want.
    - As UE doesn't allow for namespaces AND BP-compatibility, this is verbose. We recommend more liberal use of `auto` when dealing with Code-Gen API Types.
    - At runtime, don't forget to pass in any the `UObject* CallingContext` parameter: any `UWorld`, `UGameInstanceSubsystem`, `UActorComponent` or `AActor` will do.

- `UBeamBackend`, `UBeamNotifications` and `UBeam_____Notifications` are discussed in the sections below.

## `UBeamBackend`
This is the most important `UEngineSubsystem` in the SDK. It leverages Unreal's `HTTP` module to make requests to the configured Beamable backend.
It contains the implementations used by the `UBeam____Api` classes to make the actual requests. 

These implementations handle:

- Request/Response serialization, deserialization and memory lifecycle.
- Configurable Retry Logic with per-request-type, per-user-slot and per-call-site granularity.
- Request's response Cache-ing, though this is disabled by default as caching is a very context dependent endeavor.
- Transparent and Automatic Re-Auth in case of expired `AccessToken` through a user's `RefreshToken`.

We have a few different types of requests and 4 implementations to handle them:

- **CPP and BP Authenticated Requests**: require an `FUserSlot` with a logged-in user whose access token we'll use to make the request. 
- **CPP and BP Non-Authenticated Requests**: does not require an `FUserSlot` with a logged-in user.
- **`UBeamBackend::CreateGenericBeamRequest`**: for making requests to non-Beamable servers by `UBeamGenericApi`.

In addition to these implementations, we also have a hierarchy of retry configurations. 
You can configure these in `UBeamCoreSettings` (`Project Settings -> Beamable Core`).
Retries happen automatically on timeouts and a few other known cases. By default, these are:

- The `FBeamErrorResponse` structure received is a `408` status.
    - The Unreal HTTP Request returning a `EHttpFailureReason::ConnectionError` or `EHttpFailureReason::TimedOut` are parsed into `FBeamErrorResponse` with a `408`.
- We got any errors defined in `UBeamBackend::AUTH_ERROR_CODE_RETRY_ALLOWED`.
    - These errors trigger out seamless authentication token refreshing flow. It'll refresh the token and then retry the request.

If you ever encounter issues with this system, `log LogBeamBackend Verbose` is a useful Unreal command that can be used as a diagnostic tool.
It will print out the entire process of building the request, sending it out and receiving its response.

!!! note "Connectivity"
    In the Beamable SDK, we do NOT handle the concept of "player connectivity to the internet" via request/response heuristics. 
    See `UBeamNotifications` below and [Connectivity](connectivity.md) for more information.

!!! note "Request/Response Object Lifecycle"
    When we deserialize every request's response, all its `UObject` instances are created with the Request `UObject` instance as its `Outer` parameter. We ensure that, as long as there are running Operations and Waits depending on that Request, all of its `UObject` instances will not be garbage collected. However, after said Operations/Waits are done, we'll no longer keep a reference to the Request's `UObject`. This means that, if you want to cache or use any `UObject` instance from the Response hierarchy, you need to keep a reference to the Request `UObject` yourself.   

## `UBeamNotifications`
Every Beamable player has an open WebSocket connection to the Beamable server while they are logged-in. 
This system leverages UE's `WebSocket` module to open web-socket connections for each logged-in user (using `FUserSlot`).

This WebSocket connection semantically represents the connectivity status for that particular user. 
This means the SDK (and the Beamable Servers) think that a user is online/offline based on whether this connection is alive and well.
Which in turn means that, if you want to use any of our real-time services ([Matchmaking](../beamable-services/matchmaking.md), [Lobbies](../beamable-services/lobbies.md), etc...)
this connection needs to be properly working. At runtime, `UBeamRuntime` and `UBeamConnectivityManager` handle per-`FUserSlot` [Connectivity](connectivity.md) statuses.

Aside from defining [Connectivity](connectivity.md) semantics, this connection is also how the Beamable servers (or your own custom Microservices) send notifications to clients about certain events.

For example:

- Implementations of `UEngineSubsystem` called `UBeam_____Notifications` exist for each Beamable Services (that emit notifications).
    - These expose two UE function versions, one BP-Compatible and the other Lambda-Compatible, that register a handler to process a specific type of notification.
- These are used by that service's `UBeamRuntimeSubsystem` based on their semantic needs.
    - For example, `UBeamMatchmakingNotifications` subscribes to notifications for the matchmaking ticket while a `FUserSlot` is on a given queue.
- You can use Microservices to send out custom notifications --- those can be received in clients by creating your own subsystem modeled after these.
    - Use `UBeamRuntime::SubscribeToCustomNotification` to subscribe to these easily at runtime. 
  
