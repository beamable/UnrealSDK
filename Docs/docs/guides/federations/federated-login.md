# Federated Login
Login Federation is Beamable's approach to integrating 3rd Party Authentication with various platforms. You can find working examples of this federation in both [Steam](../samples/basic/steam-demo.md) and [Discord](../samples/basic/discord-demo.md) Samples.

This Federation is always [invoked In-Band](../guides/federation.md#federation-calls) and via the `Login_____`,  `SignUp____` and `Attach____` functions of the `UBeamRuntime` subsystem class.

Its interface has a single function called **Authenticate** with the following signature:

```csharp
public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge, string solution);
```

!!! warning "2FA"
	You can implement 2FA with this. That's the purpose of the `challenge` and `solution` parameters. However, the UE SDK doesn't officially support this yet.

The purpose of this function is:
> Map a 3rd Party token to a Unique Identifier for the user within the 3rd Party.

Most of the time, you achieve this by doing the following:

1. \[**Game Client**]: Use the 3rd Party Client SDK to get a token of sorts.
	1. See our [Steam](../samples/basic/steam-demo.md) and [Discord](../samples/basic/discord-demo.md) Samples for examples of this.
2. \[**Game Client**]: Invoke a `Login`/`SignUp`/`Attach` **Operation** and pass the following parameters:
	1. **MicroserviceName**: this is the name of the Microservice (the **csproj** file name, in the default case).
	2. **IdentityNamespace**: this is the Federation's **[Federation Id](../concepts/federation.md#federation-id)**. Passing this in informs Beamable which federated login to invoke as part of the account creation/attach flow.
	3. **IdentityUserId**: this is the 3rd Party's `UserId` for the user trying to login. We use this to determine if there's already a Beamable account mapped to this 3rd Party Id.
	4. **IdentityAuthToken**: this is a token that for the user that can be used by the `Authenticate` function to map it back to a `UserId`.

After this, the flow goes into your `Authenticate` function. What that function should do, depends on whether or not you are implementing 2FA or not.

#### Federated Login - without 2FA
Semantically, there are two ways the `Authenticate` function can be called:

- **Account Creation Time**: When using **`UBeamRuntime`'s  `LoginExternalIdentity` or `SignUpExternalIdentity` Operations**. 
- **Account Attach Time**: When using **`UBeamRuntime`'s  `AttachExternalIdentity` Operations**. 

In both cases, what you want to do is:

1. Use the 3rd Party's APIs or C# SDKs to validate the provided `token`.
2. Use the 3rd Party's APIs or C# SDKs to get the `UserId` for that `token`'s user.
3. Return `UserId` the `FederatedAuthenticationResponse` .

The main different between both cases is that:

- **Account Creation Time**: `Context.UserId` is `0`; as at this time, no account exists.
- **Account Attach Time**: `Context.UserId` is a valid `GamerTag`; as you are adding an identity to an existing account.

For non, 2FA flows (which are most of the Store and Console login flows) this is all that is needed.

#### Federated Login - 2FA
Semantically, there are an additional two ways that the Authenticate function can be called:

- **Without a `challenge`/`solution`**: This is the first part of the flow. 
	- Here, your function should generate a `challenge` and return it in the `FederatedAuthenticationResponse`.
	- The `UserId` in `FederatedAuthenticatedResponse` should be empty in this first step.
	- 3rd Party SDK's that support/require 2FA will typically provide you a function to generate said challenge.
	- The `challenge` is sent back to the client who should then solve it.
	- After solving the challenge, the client must invoke `Login`/`Attach` again, but now passing in the `challenge` and `solution`.
- **With a `challenge`/`solution`**: This is the second part of the flow.
	- If the `solution` is not empty, the `Authenticate` function should validate it against the `challenge`.
	- If successful, the function should then return a valid `UserId` in `FederatedAuthenticationResponse`.

!!! warning "UE SDK Support"
	This flow's usability in the engine SDK is not particularly good right now. You can achieve this by writing your own implementation of `Login`/`Attach` that maps better to 2FA than the existing ones.
	
	This is a high priority issue for us and better 2FA support should be done in the next minor release.