# Identity
The Beamable SDK comes with a set of pre-implemented operations for common sign-up use-cases. Here are how to set up a few of the common login/signup flows using Beamable.

## Login Flow - "Mobile Games" Style Authentication
Mobile games often want to create a **Guest Account** for the player so they can start playing quickly and later decide if they want to `Attach` that guest account to a more permanent identity.

The SDK supports this flow via the `UBeamRuntime::InitSDKWithFrictionlessLogin` function. Initializing the SDK with this function will immediately attempt to create a **Guest Account** at the `OwnerPlayerSlot` as soon as the SDK finishes initializing itself. If an account is already locally cached at that `FUserSlot` we'll login to that one automatically without making a request to Beamable.

The `On User Ready` callback provided to the `InitSDKWithFrictionlessLogin` function runs after the Guest Account was successfully created and, at that point, you can make further requests to Beamable.

**Guest Accounts are lost if signed out (or have its locally cached data lost for any reason)**. To avoid that, players can to "attach" some persistent identity information to that guest account. `UBeamRuntime::Attach_____` do that. After a successful attach call, a player will be able to login via the corresponding `UBeamRuntime::Login____` operation. For example, if you `AttachEmailAndPassword` you'll be able to `LoginEmailAndPassword` to sign back into the account.

This user sign in flow does not run in Dedicated Servers even if `InitSDKWithFrictionlessLogin` is called. Dedicated Servers use a different form of authentication that is not based on `FUserSlots`.

## Login Flow - "PC/Console" Style Authentication
In PC/Console titles, often the user can sign-in and up from inside the game. That can happen either through an active form-filling process, an active request to third-party authentication (Discord, Google, etc...) or an automatic store-based login (Epic Online Services, PSN, Steam, etc...).

***If your game has these flows, we recommend you use `InitSDK` and manage the login/signup flows in your game code instead. The steps below explain how to do that.***

In your `BeginPlay` implementation, call `UBeamRuntime::InitSDK`. It provides you different callbacks to handle initialization success or failure. At the end of a successful initialization, you can call `UBeamRuntime::SignUp____` or `UBeamRuntime::Login____` Operations with the appropriate parameters to login a user.

You can react to the successful Login/SignUp either via registering a callback to `UBeamRuntime::OnUserReady` OR by the [operation's own events](../concepts/operations-and-waits.md).

We treat these operations as atomic inside the SDK and will clear any invalid partial state in case of any failure during their internal multi-step process; triggering `UBeamRuntime::OnUserReady` only in the case that the user is fully ready for use.
