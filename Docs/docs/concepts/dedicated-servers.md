<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Dedicated Servers

## Overview
The Beamable Unreal SDK was made with support for a dedicated servers in mind from the start. We also develop and maintain a simple [Sample Project](../samples/complex/hathora-demo.md) containing a `Dockerfile` for a Linux server container builds and a microservice example of how to integrate with a Game Server Orchestrator.

## SDK Dedicated Server Initialization
By default, each dedicated server instance it is expected to run a single lobby. When the server starts up and you call `UBeamRuntime::InitSDK`, the server will look for some overrides and parameters coming in from Environment Variables OR Command-Line Arguments. **Command Line Arguments override Environment Variables when both are present**.

The table below describe these overrides and what they are for:

| Value        | CLArg/EnvVar                                                                                                                                                                                                                                                                                                                                    |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Realm Secret | **CLArg**: `beamable-realm-secret`<br>**EnvVar**: `BEAMABLE_REALM_SECRET`<br><br>This is a **high-security token** that can be found in: `Portal -> Games -> Any Realm (...) -> Project Secret` OR by running `dotnet beam config secret` from your project root.<br><br>Be very careful with this and DON'T commit it to your version control. |
| CID          | **CLArg**: `beamable-customer-override`<br>**EnvVar**: `BEAMABLE_CUSTOMER_OVERRIDE`<br><br>This is mostly here so you can point our Sample builds to your organization; has little bearing on your own games.                                                                                                                                   |
| PID          | **CLArg**: `beamable-realm-override`<br>**EnvVar**: `BEAMABLE_REALM_OVERRIDE`<br><br>This defines with which of your realms the server will attempt to communicate. Make sure this matches the Realm Secret.                                                                                                                                    |
| Lobby <br>ID | **CLArg**: `BeamableDedicatedServerInstanceLobbyId`<br>**EnvVar**:`BEAMABLE_DEDICATED_SERVER_INSTANCE_LOBBY_ID`<br><br>The [Lobby ID](../features/lobbies.md) for the match that'll happen in this server.                                                                                                                                      |
!!! note "Multiple Lobbies per Server Instance"
    If no Lobby ID is provided via the CLArg, we assume you'll manage fetching lobby data yourself via `UBeamLobbySubsystem::CPP_RefreshLobbyDataOperation`. You can use this to manage multiple lobbies per-instance in ways more specific to your game.

## Differences from Game Client 
The SDK works a bit different when its running inside a Dedicated Server and the way we recommend you integrate your server-authoritative logic is a bit different. This section explains these differences.

### User Slots
User Slots are a big part of the regular workflow when working with Beamable SDK in game clients. For dedicated servers though they are not used. For interfaces containing the `UserSlot` parameter, that parameter can be ignored.

This means a few things:

- There is no need to `SignUp`/`Login`; just to `InitSDK`.
- Calling APIs that simply read data from users via their `GamerTag` or other Ids will work fine.
- Calling APIs that write to user data is not recommended via regular SDK functions (see below for the alternative).

### Writing User State
The current recommended way of changing user state from dedicated server code is to write a `ServerCallable` functions in Microservices and invoking those. See [Microservices](../concepts/microservices.md) for more information about the various types of `Callable`.

### Microservices & Federation
Beamable does not provide Game Server Orchestration. This means that, while we have Lobbies, Matchmaking and can find matches between players, we do NOT run the actual Game Server. For this, we partner with other companies and provide a simple way to integrate our Matchmaking and Lobbies with them.

You can read more about this in the [Federated Game Server](../guides/federations/federated-game-server.md) guide, but conceptually here's what happens:

1. Players are in a Matchmaking queue or Lobby.
2. A Match is found or a Lobby leader asks for a Game Server for their match.
3. The Beamable Backend calls a Microservice (configured via the `UBeamGameTypeContent`).
	1. This call is expected to provision the game server and return a `ServerInfo` object.
	2. This object should contain all sorts of information for the match including connection information.
	3. The data in this object gets appended to the Lobby's `GlobalData` and Lobby Player's `Tags`.
	4. When the Game Server Instance starts up, the SDK fetches the Lobby data for the match and these properties will be there.
4. The Beamable Backend then notifies all relevant game clients that the server is ready.
5. The SDK detects that and invokes a callback where you can read set properties.

Our [Hathora Sample Project](../samples/complex/hathora-demo.md) contains example of the flow above.