# Federated Player Init
Player Init Federation is Beamable's approach defining your user's initial state. You can find working examples of this federation in the [BeamBall](../../samples/beamball-demo.md) and [LiveOps](../../samples/live-ops-demo.md) Samples.

This Federation is always [invoked In-Band](federation.md#federation-calls) and via the `LoginFrictionless` and `SignUp____` Operations of the `UBeamRuntime` subsystem class.

Its interface has a single function called **CreatePlayer** with the following signature:

```csharp
public async Promise<PlayerInitResult> CreatePlayer(Account account, Dictionary<string, string> properties);
```

The purpose of this function is:

> Leverage the Beamable Content, Stats and Inventory APIs to define the initial state for the account being created. 


## How to Use this Federation

1. In the client-code, call `LoginFrictionless` or one of the SignUp operations. 
   1. You can optionally pass in some data in the `InitProperties` parameter of these operations. This data will show up in the `properties` parameter of the federated function.
2. After the account is created and ready for use, but **_before the those operations complete in the client_**, your microservice `CreatePlayer` function will run.
   1. If the `CreatePlayer` function fails, it'll fail the operation in the client. In other words, the login/signup fails entirely UNLESS this function works properly.
   2. Inside the `CreatePlayer` function, use `Services.Inventory` and `Services.Stats` to add/remove things from the player's stats/inventory. 
3. In the client-code, register your `OnUserReady` callback implementing what your client does when the user signs in/up.
   1. At this point, the client already has the things you added to the players stats/inventory in the `CreatePlayer` function and you can use the APIs of the `UBeamStatsSubsystem` and `UBeamInventorySubsystem` to read that data. 

!!! note "Failures in `CreatePlayer`"
    Because failing in this function means the account creation failed entirely, your downstream code of this operation can assume that the initial state exists which makes it simpler to write/maintain. 

    This also means that you can handle any custom failure cases of your custom initialization in the client operation's failure handler code. 



