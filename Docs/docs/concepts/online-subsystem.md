To use our Online Subsystem integration, you'll need to update your `*.Target.cs` 's `Beam.ConfigureGame` method call. As well as re-running, `beam-init-game-maker.sh "Path/To/SDK/Clone" true` with a second argument as true.

To enable the Enabling Online subsystem would require updating the value of the second argument of that method, `Beam.OssConfig` value, example values for Hathora sample project:

```csharp
var oss = new Beam.OssConfig()
{
    IsEnabled = true,

    HooksEnabled = true,
    HookSubsystemImplementation = "FOnlineSubsystemHathoraDemo",
    HookSubsystemIncludePath = "Customer/OnlineSubsystemHathoraDemo.h",

    AdditionalHookModules = new[] { "HathoraSDK" }
};
```

## Login, Attach and Signup
There are several different styles of signup/login flows games might want to use. This section explores how to set them up.

### Frictionless Login + Attaching Identities
This flow is useful for when you want to automatically create a user for the player and then, some time in the future, you'll provide your player the opportunity to attach identities to them. Mostly used by mobile games, but can also be used to implement automatic Steam/Epic store logins.

- Use the `IOnlineIdentity::Login` function with a `LoginType` of `BeamOSS::GetIdentityTypeFrictionless()` to create an account (or sign into the locally cached one). 
- Then, while signed into to an account, call `Login` again with a `LoginType` of `BeamOSS::GetIdentityTypeAttach____()` to attach a new identity to the currently logged in account.
	- Don't forget to reassign the callbacks on `OnLoginCompleteDelegates` before calling login to respond to success/failure of attaching.

!!! warning "Swapping Accounts when Attaching"
	If you have `UOnlineSubsystemBeamableSettings::bAutoLoginOnAttach` set to `true`, trying to attach to an already-used identity will sign out of the current user and then sign-in to the given identity. Keep in mind the difference in the semantics of the `OnLoginCompleteDelegates` because of this.
	
	Ex: `User A` is signed into `Player0` and you try to attach an email belonging to `User B` to `Player0`. If `bAutoLoginOnAttach == true`, `User A` will be signed out of `Player0` and `User B` will be signed in and only then the `OnLoginCompleteDelegates` will trigger as a success.

## Manual Sign-Up/Login with Email/Password
If your game has a sign-up and/or login screen that the user is expected to choose their sign-up or login flows, this is what you want.

-  Use the `IOnlineIdentity::Login` function with a `LoginType` of `BeamOSS::GetIdentityTypeSignUpEmail()`.
- If you have `UOnlineSubsystemBeamableSettings::bAutoSignUpWhenLogin` set to `true`, you can use `BeamOSS::GetIdentityTypeEmail()` and it'll automatically create an account if the credentials provided aren't already associated with an account (if they are, you'll sign into the provided credentials).

!!! note "Attaching Other Identities"
	You can still attach other identities using any of the `BeamOSS::GetIdentityTypeAttach____()`. The same rules around `bAutoLoginOnAttach` apply.
## Automatic Third-Party via Store + Attaching Identities
If your game uses some third-party store identity such as Steam/Epic Store, you can follow this flow. This requires you to have correctly setup an identity federation for the store (see [each federation's How-To guides for more information](../guides/federations/federated-login.md)).

- Use the `IOnlineIdentity::Login` function with a `LoginType` of  `BeamOSS::GetIdentityTypeFederated()` with `UOnlineSubsystemBeamableSettings::bAutoSignUpWhenLogin` as `true`.
	- Each third-party identity may require different inputs. This depends on how your federation is set up. You can see our [Discord](../samples/basic/discord-demo.md) and [Steam](../samples/basic/steam-demo.md) samples for examples of how to write these federations.

!!! note "Attaching Other Identities"
	You can still attach other identities using any of the `BeamOSS::GetIdentityTypeAttach____()`. The same rules around `bAutoLoginOnAttach` apply.