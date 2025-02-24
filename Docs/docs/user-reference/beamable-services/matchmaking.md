# Matchmaking
## Overview

The Beamable SDK Matchmaking feature allows player to join a matchmaking queue (defined by a `UBeamGameTypeContent` instance), configure rules for matches to be made, receive notifications of progress and, optionally, provision a Game Server with a 3rd Party Game Server Orchestrator for the resulting match. 

## `UBeamGameTypeContent` as Queues
Beamable's Matchmaking system depends on Beamable's [Content System](content.md) in order for you to define various matchmaking queues.

Each Matchmaking queue is described by a `UBeamGameTypeContent`. This content type defines a few things about a queue:

- `TArray<FBeamMatchmakingTeamRules> Teams`: Defines the number of teams (one per entry in the array) and, for each of those teams, defines the number of players and a name.

!!! note "Dynamic Team Sizes"
	This is for fixed-team-size queues. For teams that are built *after* the match is made, you can use the resulting [Lobby](../features/lobbies.md)'s data and [Federated Game Servers](../federation/federated-game-server.md) to compute and store the dynamic team split.

- `FOptionalBeamStatComparisonRule EntryRules`: Optionally defines a set of [Stat](stats.md) comparison rules. Only players whose [Stats](stats.md) match those comparisons will be allowed into this queue.

!!! note "Gating on Rank"
	Failing to meet entry rule requirements will cause the Join Operation to fail --- so these can be used to gate queues on a player's account level or rank for example.

- `Numeric Rules` and `String Rules`: These are match grouping rules.
	- **Numeric Rules** tries to group players with a particular stat within certain delta range.
	- **String Rules** groups players whose values for a particular stat match a certain value.

!!! note "Grouping by WinRate"
	If you compute and store an Win Percentage value in a `Stat`, for example, you can tell the queue to group players that are closer in win-rate than others using **Numeric Rules**.

- `MaxWaitDurationSecs`: Defines how long the player can stay in the queue without being matched; after this time passes, the matchmaking fails and `OnMatchTimedOut` is triggered.
- `MatchingIntervalSecs`: Defines the ticking interval for the queue. Defaults to 10 seconds, which means that new sets of matches are produced every 10 seconds.
	- If the time it takes to tick a queue is longer than the value set here, the longer value becomes the new tick.
- `FederatedGameServerNamespace`: Defines a [Federation Id](../federation/federation.md#federation-id) for a [Federated Game Server](../federation/federated-game-server.md) federation.

## Joining/Leaving Queues
The **Matchmaking Subsystem** the SDK provides out of the box provides you a few things:

- A "Join a Queue" Operation.
- A "Leave a Queue" Operation.
- A "I'm in the queue, but wasn't matched yet" callback (`OnMatchSearching`)
- A "I was in the queue for too long without a match" callback (`OnMatchTimedOut`)
- A "I got matched and my match is ready" callback (`OnMatchReady`)
- A "I left the queue before getting matched" callback (`OnMatchCancelled`)

!!! warning "Party System"
	Beamable's backend supports party matchmaking. The `OnMatchRemoteSearchStarted` and `OnMatchCancelled` are how a party member who is not the leader becomes aware that the leader has joined/left a queue for their party.
	
	 The SDK does not have nice ergonomics for using this yet, but it is possible to use our Party system writing your own operations on top of `UBeamPartyApi`.

Each player can only be in a single queue at a time. When joining a queue, you can optionally pass in a set of key/value pairs called `FBeamTag`. When a match gets made with that particular user/party, these tags end up inside the [Lobby](lobbies.md)'s per-player data. If you're in a party, the party leader is the only one allowed to join a queue on behalf of the party.

!!! warning "Party and Tags"
	When joining a queue as the party leader and passing in `FBeamTag`, those tags are only for the party leader. If you need to gather data for every user, we recommend using [Federated Game Server](../federation/federated-game-server.md) and [Stats](stats.md) to get that data into the [Lobby](lobbies.md) instead.

Leaving a queue is very straight-forward; just call the function with the appropriate `FUserSlot` and at the end of the Operation the "matchmaking ticket" will be invalidated and you'll no longer be in the queue. When using this, keep in mind that the ticket is only invalidated *after* the operation completes; not after this function is called.

### Match Found and Tickets
When you join a queue in Beamable's matchmaking, you get back a `FBeamMatchmakingTicket`. This ticket contains information about the entry onto the queue:

- **GameType** is the queue type.
- **GamerTagsInTicket** hold the list of players that are in the ticket.
- **SlotsInTicket** hold the list of local `FUserSlot` that are in the ticket (just the Owner Player, unless your game has multiple local players and matchmaking).
- **FoundMatchLobbyId** is only filled inside the `OnMatchReady` callback and has the id for the resulting [Lobby](lobbies.md) for the match. You can use this to retrieve data from the [Lobby Subsystem](lobbies.md) inside the `OnMatchReady` callback to get connection information and more.

If you want to understand a bit more about these tickets, we recommend taking a look at the source code of the `UBeamMatchmakingSubsystem` (it is pretty simple and should give you a lot more confidence in understanding the system).
## Getting Started
To use `UBeamMatchmakingSubsystem` via blueprints (or C++), you'll need to:

- Use the [Content Window](content.md) to create a `game_type` content with a single team with a Min/Max player count of 1.
- Publish that content to your realm.
- Assign delegates to `OnMatchReady`, `OnMatchCancelled`, `OnMatchTimedOut`, so on...
- Call `TryJoinQueueOperation` with the signed in `FUserSlot` and the created `game_type` content.
- After a short duration, you should see the `OnMatchReady` callback being triggered with a lobby containing just you as a player.
- That is it!

!!! warning "Loggin in"
	Make sure that user is logged in when the code above runs. See our [Identity](identity.md) documentation