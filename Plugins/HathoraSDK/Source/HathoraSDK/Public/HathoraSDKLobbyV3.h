// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDK.h"
#include "HathoraSDKAPI.h"
#include "HathoraTypes.h"
#include "Misc/DateTime.h"

UENUM(BlueprintType)
enum class EHathoraLobbyVisibility : uint8
{
	// The player who created the room must share the roomId with their friends.
	Private,

	// Visible in the public lobby list, anyone can join.
	Public,

	// For testing with a server running locally.
	Local,

	Unknown UMETA(Hidden)
};

struct FHathoraLobbyInfo
{
	// User-defined identifier for a lobby. Defaults to the RoomId
	// if a ShortCode was not specified in CreateLobby().
	FString ShortCode;

	// When the lobby was created.
	FDateTime CreatedAt;

	// Email address for the user that created the lobby.
	FString CreatedBy;

	// Optional configuration parameters for the room.
	// Can be any string including stringified JSON.
	// String is empty if null or not set.
	FString RoomConfig;

	// Types of lobbies a player can create.
	EHathoraLobbyVisibility Visibility = EHathoraLobbyVisibility::Unknown;

	// Which region the lobby is in.
	EHathoraCloudRegion Region = EHathoraCloudRegion::Unknown;

	// Unique identifier to a game session or match.
	FString RoomId;

	// System generated unique identifier for an application.
	FString AppId;
};

struct FHathoraLobbyInfoResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	FHathoraLobbyInfo Data;
};

struct FHathoraLobbyInfosResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	TArray<FHathoraLobbyInfo> Data;
};

class HATHORASDK_API FHathoraSDKLobbyV3 : public FHathoraSDKAPI
{
public:
	
	static FHathoraSDKLobbyV3* Instance();
	
	DECLARE_DELEGATE_OneParam(FHathoraOnLobbyInfo, FHathoraLobbyInfoResult);

	// Create a new lobby for an application. A lobby object is a wrapper around a room object.
	// With a lobby, you get additional functionality like configuring the visibility of the room,
	// managing the state of a match, and retrieving a list of public lobbies to display to players.
	// @param Visibility Types of lobbies a player can create.
	// @param RoomConfig Optional configuration parameters for the room. Can be
	//                   any string including stringified JSON. It is accessible
	//                   from the room via GetRoomInfo().
	// @param Region The region to create the room in.
	// @param ShortCode Optional user-defined identifier for a lobby. Leave empty
	//                  to reference the lobby using the RoomId only.
	// @param RoomId Unique identifier to a game session or match. Leave empty to
	//               use the default system generated ID.
	void CreateLobby(
		EHathoraLobbyVisibility Visibility,
		FString RoomConfig,
		EHathoraCloudRegion Region,
		FString ShortCode,
		FString RoomId,
		FHathoraOnLobbyInfo OnComplete
	);

	DECLARE_DELEGATE_OneParam(FHathoraOnLobbyInfos, FHathoraLobbyInfosResult);

	// Get all public active lobbies for a given application. Use this endpoint to display
	// all public lobbies that a player can join in the game client. Use
	// ListRegionActivePublicLobbies() to only see lobbies in a specific region.
	void ListAllActivePublicLobbies(FHathoraOnLobbyInfos OnComplete);

	// Get all active lobbies for a given application, filtered by Region.
	// Use this endpoint to display all public lobbies that a player can join
	// in the game client. Use ListAllActivePublicLobbies() to see all lobbies.
	// @param Region Filter the returned lobbies by the provided region.
	void ListRegionActivePublicLobbies(EHathoraCloudRegion Region, FHathoraOnLobbyInfos OnComplete);

	// Get details for a lobby.
	// @param RoomId Unique identifier to a game session or match.
	void GetLobbyInfoByRoomId(FString RoomId, FHathoraOnLobbyInfo OnComplete);

	// Get details for a lobby. If 2 or more lobbies have the same shortCode, then the most
	// recently created lobby will be returned.
	// @param ShortCode User-defined identifier for a lobby.
	void GetLobbyInfoByShortCode(FString ShortCode, FHathoraOnLobbyInfo OnComplete);

private:
	static FString GetVisibilityString(EHathoraLobbyVisibility Visibility);
	static EHathoraLobbyVisibility ParseVisibility(const FString& VisibilityString);

	void ListActivePublicLobbies(TArray<TPair<FString, FString>> QueryOptions, FHathoraOnLobbyInfos OnComplete);

	static FHathoraLobbyInfo ParseLobbyInfo(TSharedPtr<FJsonObject> LobbyInfoJson);
};
