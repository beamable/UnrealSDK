<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Dedicated Servers

## Overview

Beamable SDK is made with support for a dedicated servers in mind from start. There is developed [Hathora Sample Project](../samples/hathora-demo.md) which contains working project with dedicated server support and Dockerfile for a Linux server container builds.

## Differences from client code

### User Slots

User Slots are a big part of the regular workflow when working with Beamable SDK. For server though they are not used. 

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
