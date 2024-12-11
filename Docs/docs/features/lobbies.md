<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Lobby
Beamable's Lobby system can be used primarily for 2 cases:

- **Open/Closed Custom Lobbies/Rooms**: Player-created custom rooms for room-based games
- **Resulting Matchmaking Matches**: Matchmaking queues output lobbies with players in them at each matchmaking queue. See more in [Matchmaking](../features/matchmaking.md).

Conceptually, Lobbies are room containing only online players and a set of arbitrary room properties and player properties. There are a few rules you should be aware off:

- Each Non-Matchmaking Lobby has a **Host** and other Players.
- Becoming offline will remove you from the lobby (after a small delay).
- The host player becoming offline will disband a lobby (after a small delay).
- The host player can edit global properties and any other player's properties.
- The host player can kick other players whereas regular players can only leave themselves.
- Players can **read** the entire lobby data but only **write** to their own state.
- Matchmaking Result Lobbies have no host; instead they disband once every player is offline.

We'll focus on how lobbies work and which operations can be made within them.
## Lobby Types and Schema
There are two types of lobbies: **Open** and **Closed** lobbies. **Open** lobbies can be queried via `RefreshLobbies` and joined without the use of any passcode. **Closed** lobbies are not visible to `RefreshLobbies` and expect to be joined via the generated passcode.

Both lobby types have the same schema and are represented by the `ULobby` class. This class has several properties:

- **LobbyId**: The unique identifier for the Lobby.
- **MatchType**: Contains information about the `UBeamGameTypeContent` that is associated with the lobby.
- **Name** and **Description**: Are arbitrarily defined when the lobby is created.
	- For matchmaking, these are empty.
- **Host**: The host player's `FBeamGamerTag`. 
	- For matchmaking result lobbies, there is no host. // Federation thing: Make a section here explaining LoL-style matchmaking where player properties change after the match is made but BEFORE the server is provisioned.
- **Restriction**: Defines whether the lobby is **Open** or **Closed**.
	- Can be changed --- whenever it is changed to **Closed**, a new **Passcode** is generated.
- **Passcode**: An auto-generated realm-scoped unique value that can be use to `JoinLobbyByPasscode`.
	- This is filled on-creation and the passcode length has a minimum of 6.
- **MaxPlayers**: Defines the maximum amount of players that can be in this lobby at the same time.
	- When changing this via `CommitLobbyUpdateOperation`, if you have more players than the new **MaxPlayer** value, you'll get an error.
- **Players**: A list of `ULobbyPlayer` containing data associated to each player in the lobby.
	- **PlayerId**: The player's `FBeamGamerTag`.
	- **Joined**: A ISO-8601 Date Time string for when the player.
	- **Tags**: An array of Key-Value pairs (allows duplicates).
- **Data**: An arbitrary data store that can be filled and updated by the host of the lobby.
	- Can be filled via [Federation](../guides/federations/federated-game-server.md) as well.
- **Created**: A ISO-8601 Date Time string for when the Lobby was created.

## Hosting Lobbies
To use the SDK to enable a player to host a Beamable Lobby, you'll need the following:

- `CreateOpenLobbyOperation` OR `CreateClosedLobbyOperation` to create the actual lobby.
- `UpdatePlayerDataOperation`, `DeletePlayerDataOperation` and `KickPlayerOperation` to manage players and their in-lobby data.
- `CommitLobbyUpdateOperation` to manage lobby settings and `Data`.
	- This can be used in conjunction with `TryBeginUpdateLobby` and the set of `Prepare____` functions to batch the changes along in order to minimize requests made.
- For dedicated server games, use `ProvisionGameServerOperation` and [Federation](../guides/federations/federated-game-server.md) to boot up a server instance for the game.

!!! note "About Parties"
	Only the party leader is allowed to create a Lobby. Doing so will also places all party members into the created Lobby.

#### Hosts & Disbanding
By default, whenever a host leaves the lobby, Beamable will disband the lobby and notify all players in it. However, in some games, the desired behavior is different:

- Leader Leaves the Lobby
- Another Player in the Lobby is Promoted to Leader.

This can be accomplished by using the SDKs `TryBeginUpdateLobby`, `PrepareUpdateHost` and `CommitLobbyUpdateOperation` ***before*** using the `LeaveLobbyOperation` to exit the lobby.
## Joining Lobbies
To use the SDK to enable a player to join and manage its settings inside a Beamable Lobby, you'll need the following:

- `RefreshLobbyOperation`, `KnownLobbies` and `JoinLobbyOperation` to find and join an **Open** lobby.
- `JoinLobbyByPasscodeOperation` to join an existing **Closed** lobby.
- `UpdateSlotPlayerDataOperation` and `DeleteSlotPlayerDataOperation`.
- `LeaveLobbyOperation` to leave the lobby should you want to step out of it.

!!! note "About Parties"
	Only the party leader is allowed to join a Lobby. Doing so will also bring all other party members into the Lobby with them. If the Lobby **MaxPlayer** count would be surpassed by the entire party joining, nobody can join.
## Synchronizing across Clients
Beamable's Lobby system will automatically notify every player inside a lobby of relevant events. Once you're in a lobby, the SDK keeps track of your local state inside `UBeamLobbyState` (one per-`UserSlot`). 

You can use `GetCurrentSlotLobbyState` to get the `UBeamLobbyState` and setup various **Delegates** in this object to respond the these events, normally updating your UI or custom system built on top of this subsystem. 

!!! note "What to Sync?"
	The actual `ULobby` is kept in-sync by the Beamable SDK! You need **only** update your UI or custom system data in response to things happening in the lobby system.

Here's the list of events we expose:

- **OnKickedFromLobby**: Received whenever a host removes a player from the lobby via `KickPlayerOperation`.
	- Every player in the lobby receives this notification, including the host.
- **OnLeftLobby**: Received whenever a player leaves the lobby via `LeaveLobbyOperation`.
	- Every remaining player in the lobby receives this notification.
- **OnLobbyDisbanded**: Received whenever the host player leaves.
	- Every remaining player in the lobby receives this notification. The host does not receive it.
- **OnLobbyUpdate**: Whenever any property of the lobby changes via `CommitLobbyUpdateOperation`, `UpdatePlayerDataOperation` and `UpdateSlotPlayerDataOperation`, this will be invoked.


