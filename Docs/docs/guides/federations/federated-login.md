# Federated Login
Login Federation is Beamable's approach to integrating 3rd Party Authentication with various platforms. You can find working examples of this federation in both [Steam](../samples/basic/steam-demo.md) and [Discord](../samples/basic/discord-demo.md) Samples.

This Federation is always [invoked In-Band](../guides/federation.md#federation-calls) and via the `Login_____`,  `SignUp____` and `Attach____` functions of the `UBeamRuntime` subsystem class.

Its interface has a single function called **Authenticate** with the following signature:

```csharp
public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge, string solution);
```

!!! warning "2FA"
	You can implement 2FA with this. However, the UE SDK doesn't officially support this yet.
	That's what the `challenge` and `solution` parameters are used for.

This guide describes how to implement any 3rd Party Auth with FederatedLogin.
### Login with a Federated Login
There are two cases here: **with Frictionless Authentication** and **with Manual Login/SignUp**.



### Attaching an Identity to an existing Account

No GamerTag = Account Creation
Has GamerTag = Attach

Map Token to some Unique UserId within the space of possible ids of the third party.

