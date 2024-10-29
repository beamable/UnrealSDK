<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Dedicated Servers

## Overview

Beamable SDK is made with support for a dedicated servers in mind from start. There is developed [Hathora Sample Project](../samples/hathora-demo.md) which contains working project with dedicated server support and Dockerfile for a Linux server container builds.

## Server specific flow

When running dedicated server it is expected to run a single lobby match. Lobby ID can be passed as a command line argument `BeamableDedicatedServerInstanceLobbyId=ID_HERE` or with environment variable `BEAMABLE_DEDICATED_SERVER_INSTANCE_LOBBY_ID`. If no value is provided, it will be assumed that the user will run multiple matches per server and will make the calls to RefreshLobbyDataOperation from their integration with their game server orchestrator.

Another thing worth noting is the fact that there is no `OnReady` call since no user account is used on server side. There is still option to perform requests to Beamable backend by using Signed Requests. Using them is handled automatically, but requires to provide the Realm Secret to the server via command line or environment variable. In the same way it is possible to setup server customer and realm config as described in table below:

| Value      | Command line argument      | Environment variable |
| ------------- | ------------- |-------------  |
| Realm secret | `beamable-realm-secret` | `BEAMABLE_REALM_SECRET` |
| Beamable Customer ID (CID) | `beamable-customer-override` | `BEAMABLE_CUSTOMER_OVERRIDE` |
| Beamable Realm ID (PID) | `beamable-realm-override` | `BEAMABLE_REALM_OVERRIDE` |
| Dedicated Server Lobby ID | `BeamableDedicatedServerInstanceLobbyId` | `BEAMABLE_DEDICATED_SERVER_INSTANCE_LOBBY_ID` |

Realm Secret can be aquired easily from command line in the project directory by calling command `dotnet beam config secret`.

## Differences from client code

### User Slots

User Slots are a big part of the regular workflow when working with Beamable SDK. For server though they are not used. For interfaces containing the `UserSlot` parameter, that parameter is not used.

### Microservices

Implementing server that would support matchmaking will require creating `Microservice` that will implement the `IFederatedGameServer` interface. That means implementing `Promise<ServerInfo> CreateGameServer(Lobby lobby);` method that will return `ServerInfo`:

```csharp
public class ServerInfo
{
    public Dictionary<string, string> globalData;
    public Dictionary<string, Dictionary<string, string>> playerData;
}
```

[Hathora Sample Project](../samples/hathora-demo.md) contains example of the implementation.

### Online Subsystems

Beamable can be used with Unreal Online Subsystem. `*.Target.cs` project build configuration file should already contain `Beam.ConfigureGame` method call. Enabling Online subsystem would require updating the value of the second argument of that method, `Beam.OssConfig` value, example values for Hathora sample project:

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