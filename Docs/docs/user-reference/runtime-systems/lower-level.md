### Lower-Level SDK Subsystems

This section talks about lower-level details of how requests to Beamable get made. ***You don't need to read this***, but... you might want to if you plan on implementing your own `UBeamRuntimeSubsystem`. Here's why you'd want to do this:

- You want to replace one of our implementations with something quite custom and want to provide guarantees about your system's lifecycle that are similar to the ones we provide.
- You wish to guarantee that `On User Ready` has access to custom data fetched via Microservices and Microstorages.

We don't recommend writing your own unless you're confident you understand the topics below and are trying to solve one of the two problems listed above.

!!! warning "Low Level Usage"
    The systems described here are used by various environments the Beamable SDK runs in: PIE, Editor, Dedicated Server Builds and regular game builds. Their code is pretty heavily commented; so, feel free to read it and figure things out that way.

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
    - This is a somewhat complex subsystem so we recommend you read [operations-and-waits.md](operations-and-waits.md)
