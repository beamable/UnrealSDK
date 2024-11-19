# Federated Game Server
Game Server Federation allows you to integrate with 3rd Party Game Server Orchestrator (such as Hathora or Agones) as well as running arbitrary server-authoritative code before a lobby goes into a match.

The interface you implement looks like this:

```csharp
public async Promise<ServerInfo> CreateGameServer(Lobby lobby);
```

There are two [Federation Calls](../../concepts/federation.md#federation-calls) to this function: **Matchmaking Match Found** and **Provision Game Server for Lobby**.

### Matchmaking Match Found
This is an Out-of-Band call that happens as part of the [Matchmaking](../../features/matchmaking.md) flow:

1. Add the `IFederatedGameServer` federation to your microservice with a particular [Federated Id](../../concepts/federation.md#federated-id).
2. Set up that [Federated Id](../../concepts/federation.md#federated-id) in any `UBeamGameTypeContent`'s `federation` field.
3. Use the `UBeamMatchmakingSubsystem`'s `TryJoinQueue` operation passing along that `UBeamGameTypeContent`'s id to join the queue.
4. Once a match is made, the `CreateGameServer` federated function will be invoked with a Lobby structure containing all of the players matched together.
5. This function can then do one or more of the following things:
	1. Use a 3rd Party API to provision a game server, wait for it to spin up and add the connection information to the `ServerInfo` return object.
	2. Pre-fetch data associated from each player from [Stats](../../features/stats.md), [Inventory](../../features/inventory.md) or [Storage Objects](../../concepts/microservices.md) and add that data into the `ServerInfo` return object.
6. The returned `ServerInfo` object gets merged into the [Lobby](../../features/lobbies.md)'s global and player data.
	1. [In your game server build, the Lobby can be automatically prefetched if configured correctly](../../concepts/dedicated-servers.md).
7. The client SDK receives a notification from Beamable that a match is ready and invoke the `UBeamMatchmakingSubsystem`'s `OnMatchReady` callback for the match ticket.

You can check out our [Hathora Demo](../../samples/complex/hathora-demo.md) for more information on how to implement the actual `CreateGameServer` function.

### Provision Game Server for Lobby
Certain games allow players to [create custom lobbies](../../features/lobbies.md) manually. If those games also require invoking the federation endpoint to provision a server or run some arbitrary code, they can do so via the following steps:

1. Add the `IFederatedGameServer` federation to your microservice with a particular [Federated Id](../../concepts/federation.md#federated-id).
2. Set up that [Federated Id](../../concepts/federation.md#federated-id) in any `UBeamGameTypeContent`'s `federation` field.
3. Create a [Lobby](../../features/lobbies.md) with the `UBeamGameTypeContent`'s id.
	1. Closed/Open lobbies both work with federation.
4. Players will join the lobby and eventually become ready.
	1. Most custom lobby implementations use `UBeamLobbySubsystem`'s `UpdatePlayerTags` function to update each individual player's ready state.
5. Once all players are ready, the lobby host can invoke the `UBeamLobbySubsystem`'s `ProvisionGameServerForLobby` function.
6. This function requests that  the configured federation on the `UBeamGameTypeContent`'s `CreateGameServer` implementation.This function can then do one or more of the following things:
	1. Use a 3rd Party API to provision a game server, wait for it to spin up and add the connection information to the `ServerInfo` return object.
	2. Pre-fetch data associated from each player from [Stats](../../features/stats.md), [Inventory](../../features/inventory.md) or [Storage Objects](../../concepts/microservices.md) and add that data into the `ServerInfo` return object.
7. Once that function returns, it'll trigger `UBeamLobbyState`'s `OnLobbyUpdated` callback for the lobby each particular player is in.
	1. You can check if the connection information you generated inside `CreateGameServer` is within the lobby's global properties (`ULobby::Data`) and use that to connect all players to the newly created game server instance.

While we don't have a sample showcasing this exact case, you can still learn a lot about this from our [Hathora Demo](../../samples/complex/hathora-demo.md) sample.