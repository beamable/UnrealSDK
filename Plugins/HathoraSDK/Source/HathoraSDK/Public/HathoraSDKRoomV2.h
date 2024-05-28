// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDK.h"
#include "Misc/DateTime.h"
#include "HathoraSDKAPI.h"
#include "HathoraTypes.h"

#include "HathoraSDKRoomV2.generated.h"

USTRUCT()
struct FHathoraExposedPort
{
	GENERATED_USTRUCT_BODY();
	
	UPROPERTY()
	FString TransportType;

	UPROPERTY()
	int32 Port = 0;

	UPROPERTY()
	FString Host;

	UPROPERTY()
	FString Name;
};

struct FHathoraAllocation
{
	// If the API returns null for unscheduledAt, this will be false.
	bool bUnscheduled = false;

	FDateTime UnscheduledAt;

	FDateTime ScheduledAt;

	// System generated unique identifier to a runtime
	// instance of your game server.
	FString ProcessId;

	// System generated unique identifier to an allocated
	// instance of a room.
	FString RoomAllocationId;
};

USTRUCT()
struct FHathoraConnectionInfo
{
	GENERATED_USTRUCT_BODY();
	
	UPROPERTY()
	FString Status;

	UPROPERTY()
	FString RoomId;

	UPROPERTY()
	FHathoraExposedPort ExposedPort;

	UPROPERTY()
	TArray<FHathoraExposedPort> AdditionalExposedPorts;
};

struct FHathoraRoomConnectionInfoResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	FHathoraConnectionInfo Data;
};

enum class EHathoraRoomStatus : uint8
{
	// A process is not allocated yet and the room is
	// waiting to be scheduled.
	Scheduling,

	// Ready to accept connections.
	Active,

	// Room is unallocated from the process but can be
	// rescheduled later with the same `roomId`.
	Suspended,

	// All associated metadata is deleted.
	Destroyed,

	Unknown UMETA(Hidden)
};

struct FHathoraGetRoomInfoData
{
	// Metadata on an allocated instance of a room.
	// Use Status to determine if this value is valid.
	FHathoraAllocation CurrentAllocation;

	// The allocation status of a room.
	EHathoraRoomStatus Status = EHathoraRoomStatus::Unknown;

	TArray<FHathoraAllocation> Allocations;

	// Optional configuration parameters for the room.
	// Can be any string including stringified JSON.
	// String is empty if null or not set.
	FString RoomConfig;

	// Unique identifier to a game session or match.
	FString RoomId;

	// System generated unique identifier for an application.
	FString AppId;
};

struct FHathoraGetRoomInfoResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	FHathoraGetRoomInfoData Data;
};

struct FHathoraProcessRoomInfo
{
	// Metadata on an allocated instance of a room.
	// Use Status to determine if this value is valid.
	FHathoraAllocation CurrentAllocation;

	// The allocation status of a room.
	EHathoraRoomStatus Status = EHathoraRoomStatus::Unknown;

	// Optional configuration parameters for the room.
	// Can be any string including stringified JSON.
	// String is empty if null or not set.
	FString RoomConfig;

	// Unique identifier to a game session or match.
	FString RoomId;

	// System generated unique identifier for an application.
	FString AppId;
};

struct FHathoraGetRoomsForProcessResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	TArray<FHathoraProcessRoomInfo> Data;
};

struct FHathoraDestroyRoomResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	bool bDestroyed = false;
};

struct FHathoraSuspendRoomResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	bool bSuspended = false;
};

struct FHathoraUpdateRoomConfigResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	bool bUpdated = false;
};

class HATHORASDK_API FHathoraSDKRoomV2 : public FHathoraSDKAPI
{
public:

	static FHathoraSDKRoomV2* Instance();
	
	DECLARE_DELEGATE_OneParam(FHathoraOnRoomConnectionInfo, FHathoraRoomConnectionInfoResult);

	// Create a new room for an existing application. Poll the GetConnectionInfo()
	// endpoint to get connection details for an active room.
	// @param Region The region to create the room in.
	// @param RoomConfig Optional configuration parameters for the room. Can be
	//                    any string including stringified JSON. It is accessible
	//                    from the room via GetRoomInfo().
	// @param RoomId Unique identifier to a game session or match. Leave empty to
	//                use the default system generated ID.
	void CreateRoom(EHathoraCloudRegion Region, FString RoomConfig, FString RoomId, FHathoraOnRoomConnectionInfo OnComplete);

	DECLARE_DELEGATE_OneParam(FHathoraOnGetRoomInfo, FHathoraGetRoomInfoResult);

	// Retrieve current and historical allocation data for a room.
	// @param RoomId Unique identifier to a game session or match.
	void GetRoomInfo(FString RoomId, FHathoraOnGetRoomInfo OnComplete);

	DECLARE_DELEGATE_OneParam(FHathoraOnGetRoomsForProcess, FHathoraGetRoomsForProcessResult);

	// Get all active rooms for a given process.
	// @param ProcessId System generated unique identifier to a runtime instance
	//                   of your game server.
	void GetActiveRoomsForProcess(FString ProcessId, FHathoraOnGetRoomsForProcess OnComplete);

	// Get all inactive rooms for a given process.
	// @param ProcessId System generated unique identifier to a runtime instance
	//                   of your game server.
	void GetInactiveRoomsForProcess(FString ProcessId, FHathoraOnGetRoomsForProcess OnComplete);

	DECLARE_DELEGATE_OneParam(FHathoraOnDestroyRoom, FHathoraDestroyRoomResult);

	// Destroy a room. All associated metadata is deleted.
	// @param RoomId Unique identifier to a game session or match.
	void DestroyRoom(FString RoomId, FHathoraOnDestroyRoom OnComplete);

	DECLARE_DELEGATE_OneParam(FHathoraOnSuspendRoom, FHathoraSuspendRoomResult);

	// Suspend a room. The room is unallocated from the process but
	// can be rescheduled later using the same roomId.
	// @param RoomId Unique identifier to a game session or match.
	void SuspendRoom(FString RoomId, FHathoraOnSuspendRoom OnComplete);

	// Poll this endpoint to get connection details to a room.
	// Clients can call this endpoint without authentication.
	// @param RoomId Unique identifier to a game session or match.
	void GetConnectionInfo(FString RoomId, FHathoraOnRoomConnectionInfo OnComplete);

	DECLARE_DELEGATE_OneParam(FHathoraOnUpdateRoomConfig, FHathoraUpdateRoomConfigResult);

	// Update the roomConfig variable for a room.
	// @param RoomId Unique identifier to a game session or match.
	// @param RoomConfig Optional configuration parameters for the room. Can be
	//                    any string including stringified JSON. It is accessible
	//                    from the room via GetRoomInfo().
	void UpdateRoomConfig(FString RoomId, FString RoomConfig, FHathoraOnUpdateRoomConfig OnComplete);

private:
	static FHathoraAllocation ParseAllocation(const TSharedPtr<FJsonObject>& AllocationJson);
	static EHathoraRoomStatus ParseRoomStatus(const FString& StatusString);

	void GetRoomsForProcess(FString ProcessId, bool bActive, FHathoraOnGetRoomsForProcess OnComplete);
};
