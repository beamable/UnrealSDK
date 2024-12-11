<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Federation

**Federations** are similar to the idea **Server Side Callbacks or WebHooks** but are slightly expanded in use. It is Beamable's approach to solving extending, or some times delegating, the behavior of our Managed Services to microservices or 3rd parties.

Here are a few example use-cases that Federations as a concept means to solve:

- Implementing 3rd Party Auth Integrations with other Identity Providers
- Customizing Initial Player Account States
- Integrating Beamable Inventory with Steam Inventory or Web3 Wallets.
- Integrating with Game Server Orchestrators such as Hathora, Agones or even a custom stack.
- Etc...

Most implementations of Server-Side Callbacks are fire-and-forget (similar to a webhook). **Federations**, however, don't need to be fire-and-forget. Most **Federations** are calls made to your microservice happen as part of a particular flow, often having things happening ***before*** and/or ***after the Federated call finishes***.

Here's a high-level diagram of what federations are:

![microservices-architecture-federation-general.png](./Images/microservices-architecture-federation-general.png#center)

As such, each of the **Federations** we provide have their own semantics, usage guidelines, performance characteristics and constraints described in their own unique [How-To](../guides/federations/federated-login.md) guides.
## Federation Calls
There are two types of **Federations Calls** our Backend makes:

- **In-Band Federation Calls**
- **Out-of-Band Federation Calls**

**In-Band Federations** are any Federation call that **is in the path of a request originating from a game's client or real-time game server**. Examples of these are `IFederatedLogin`, `IFederatedInventory` or `IFederatedGameServer`(when called via the Lobby system's `ProvisionGameServer` from a client).

![microservices-architecture-federation-in-band.png](./Images/microservices-architecture-federations-in-band.png#center)

**Out-of-Band Federations** are any Federation calls that **are triggered by some server event that originates from inside the Beamable's Managed Services**. The most obvious example is `IFederatedGameServer` (when called for each match found as part of a matchmaking queue tick).

![microservices-architecture-federations-out-of-band.png](./Images/microservices-architecture-federations-out-of-band.png#center)

[For more information about the workflow implications of the difference between both **Federation Call** types, see below.](#workflows-for-developing-federations)

## Federation Id
Federations can be thought of delegates called by our server in particular points of various flows. Federation Ids are a unique `string`-based identifier that uniquely identifies a particular implementation of a federation. 

The combination of the **Federation Id** and the **Federation Type** is comparable to a function name/pointer used to assigned to an Unreal delegate; in the sense that it is used by the Beamable backend to know which implementation of a federation in your microservice it should talk to, if any.

Examples are good so:

- `IFederatedLogin` would have a different implementations for Steam and Epic auth integration, right?
- `IFederatedLogin<SteamId>` and `IFederatedLogin<EpicId>` the two different interfaces you'll need to implement. 

In other words, an id is just a unique `string` that you pass along in specific places depending on the federation to **choose between one or more federations if any should be used**.

## Adding/Removing Federations
Federations can be added and removed from services using  `dotnet beam fed` command pallet of the CLI.

In code, Federations are tied to interfaces implemented in your `Microservice` inherited class --- these federations and its ids are automatically validated by a C# Analyzer that will tell you if you've missing things.

```bash
# Adds an IFederatedLogin implementation to the MyMicroservice service with the "cool" id.
dotnet beam fed add MyMicroservice cool IFederatedLogin

# Adds an IFederatedGameServer implementation to the MyMicroservice service with the "hathora" id.
dotnet beam fed add MyMicroservice hathora IFederatedGameServer
```

```csharp
// FederationIds.cs
[FederationId("cool")]
public class CoolId : IFederationId;

[FederationId("hathora")]
public class HathoraId : IFederationId;

// MyMicroservice.cool.cs
public partial class MyMicroservice : IFederatedLogin<CoolId> { }
// MyMicroservice.hathora.cs
public partial class MyMicroservice : IFederatedGameServer<HathoraId> { }
```

After adding any federation, your IDE will likely complain that you are not implementing the functions of the interfaces above; most IDEs will then offer you the option of generating the function signatures for those interfaces. After that, all you have to do is write the code for it.

!!! note "Why do you need the `federations.json`?"
	We needed a consistent source of truth that would allow us to create the in-editor UXs *without needing the built DLL* to find which interfaces your service implements (because this is very slow and we can't guarantee this file's existence and "up-to-date-ness" easily).
	
	 This source of truth is the `federations.json` file the commands above manage for you. 
	
	This approach also allows us to detect implementation errors and emit compile-time errors for invalid or incorrect usage of microservice functionality. So... it was a win-win situation.

### Workflows for Developing Federations
Most federations are inside complex application paths. As such, you need a way to iterate on them locally, much like how you do with `Callables` (see [Microservices](../concepts/microservices.md#common-developer-workflows)). This is the reason we differentiate between In-Band calls to Federations and Out-of-Band calls to federations.

For **In-Band Calls** that reach a federated endpoint, the selected [Microservice Target](../concepts/microservices.md#microservice-routing-and-microservice-target) defines which running microservice instance will handle the federated call. In other words, you don't have to think about them.

**Out-of-Band Calls** however do not originate in the client or gameplay server so we can't access PIE's selected [Microservice Target](../concepts/microservices.md#microservice-routing-and-microservice-target). In order to solve that problem, out-of-band calls use semantic filtering logic to "steal" traffic from the realm's service. 

!!! warning "What about PROD?!"
	By default, production realm disallows ***any and all routing to microservices that are not the realm ones***. In other words, if you run a local microservice while in a Prod realm it CANNOT steal any traffic from the service that is deployed; be it **in-band** or **out-of-band**.

In order to configure these filters, you can use the **Local - Federations** tab of your **[Microservice Inspector](../concepts/microservices.md#microservice-window)**. The filters, when out-of-band calls can be made to a particular federated endpoint, are described in [each federation's How-To guides](../guides/federations/federated-game-server.md).

![microservices-window-federation.png](./Images/microservices-window-federation.png)

