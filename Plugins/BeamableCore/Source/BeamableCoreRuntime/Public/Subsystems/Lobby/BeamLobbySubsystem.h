// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataRequest.h"
#include "AutoGen/SubSystems/Lobby/DeleteLobbyRequest.h"
#include "AutoGen/SubSystems/Lobby/GetLobbiesRequest.h"
#include "AutoGen/SubSystems/Lobby/GetLobbyRequest.h"
#include "AutoGen/SubSystems/Lobby/PostLobbiesRequest.h"
#include "AutoGen/SubSystems/Lobby/PutLobbyRequest.h"
#include "AutoGen/SubSystems/Lobby/PutPasscodeRequest.h"
#include "AutoGen/SubSystems/Lobby/PutTagsRequest.h"
#include "BeamNotifications/SubSystems/BeamLobbyNotifications.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamLobbySubsystem.generated.h"

class UBeamLobbySubsystem;
class UBeamLobbyApi;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLobbyEventCode, const FUserSlot&, ULobby*, FLobbyUpdateNotificationMessage)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLobbyEvent, const FUserSlot&, Slot, ULobby*, Lobby, FLobbyUpdateNotificationMessage, RawEvt);

UCLASS(BlueprintType)
class UBeamLocalPlayerLobbyInfo : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGuid LobbyId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUserSlot OwnerUserSlot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamGamerTag OwnerGamerTag;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLobbyOwner;

	FDelegateHandle NotificationSubscriptionHandle;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyEvent OnLobbyDisbanded;
	FOnLobbyEventCode OnLobbyDisbandedCode;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyEvent OnLobbyUpdated;
	FOnLobbyEventCode OnLobbyUpdatedCode;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyEvent OnKickedFromLobby;
	FOnLobbyEventCode OnKickedFromLobbyCode;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyEvent OnLeftLobby;
	FOnLobbyEventCode OnLeftLobbyCode;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyEvent OnHostChanged;
	FOnLobbyEventCode OnHostChangedCode;

	friend bool operator==(const ULobby& Lhs, const UBeamLocalPlayerLobbyInfo& RHS)
	{
		return Lhs.LobbyId.Val.Equals(RHS.LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower));
	}

	friend bool operator==(const UBeamLocalPlayerLobbyInfo& Lhs, const UBeamLocalPlayerLobbyInfo& RHS)
	{
		return Lhs.LobbyId == RHS.LobbyId;
	}

	friend bool operator!=(const UBeamLocalPlayerLobbyInfo& Lhs, const UBeamLocalPlayerLobbyInfo& RHS)
	{
		return !(Lhs == RHS);
	}
};

UCLASS(BlueprintType)
class UBeamLobbyUpdateCommand : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamLobbySubsystem* StatsSubsystem;

public:
	explicit UBeamLobbyUpdateCommand() = default;
};

/** Stats Updated ----- Event fired whenever 1+ Stats are updated. **/

USTRUCT(BlueprintType)
struct FBeamLobbyUpdatedEvent
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamLobbyUpdated, FBeamLobbyUpdatedEvent, Evt);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeamLobbyUpdatedCode, FBeamLobbyUpdatedEvent);

/**
 * 
 */
UCLASS(BlueprintType, Config=Game)
class BEAMABLECORERUNTIME_API UBeamLobbySubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamLobbyApi* LobbyApi;
	UPROPERTY()
	UBeamLobbyNotifications* LobbyNotification;
	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	/**
	 * Configuration variable for the size of passcode created by this game.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Config=Game)
	int32 PasscodeSize;

	/**
	 * Holds information about which lobby each local player is in. 
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FUserSlot, UBeamLocalPlayerLobbyInfo*> LocalPlayerLobbyInfo;

	/**
	 * Holds the Lobby objects.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<ULobby*> KnownLobbies;

	int32 DedicatedServerLobbyIdx;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FUserSlot, UBeamLobbyUpdateCommand*> UpdateCommands;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

	/**
	 * Used when given a lobby id through CLArg or EnvVar. Keeps track of that Lobby Id.
	 */
	FGuid DedicatedServerInstanceLobbyId;

public:
	// LOCAL STATE

	/**
	 *  Gets the lobby that the given user is contained.
	 *  By default, will use the Owner user slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="UserSlot"))
	ULobby* GetCurrentLobby(const FUserSlot& UserSlot);

	/**
	 * Gets the local player lobby state.
	 * Call this to setup the various notification callbacks after a successful Join/Create operation or immediately before calling Join/Create.
	 *
	 * The callbacks exposed here are cleared automatically when you leave a lobby, but not when you join one.
	 * We also pre-warm these instances for each configured UserSlot; for Test UserSlots, we instantiate them here.
	 */
	UBeamLocalPlayerLobbyInfo* GetCurrentSlotLobbyState(FUserSlot Slot);

	/**
	 * Tries to get whatever the current local data for the given lobby id is. If you want a guarantee that this data is up-to-date call, [CPP_]RefreshLobbyOperation first.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLobby(FGuid LobbyId, ULobby*& Lobby);

	/**
	 * You should only ever use this if you are running a single Lobby/Match per instance.
	 * If you are running multiples, call TryGetLobby with the id of the lobby you want.
	 * 
	 */
	bool TryGetDedicatedServerInstanceLobby(ULobby*& Lobby);


	// OPERATIONS

	/**
	 * @brief Creates a public lobby that any player can join. If no game-type is given, the lobby cannot provision a game server.
	 * LobbyData is data associated to the lobby and PlayerTags are a set of non-unique Name/Value pairs associated to each player.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle CreateOpenLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers,
	                                              TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags);

	/**
	 * @copydoc CreateOpenLobbyOperation 
	 */
	FBeamOperationHandle CPP_CreateOpenLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers = 32,
	                                                  TMap<FString, FString> LobbyData = {}, TArray<FBeamTag> PlayerTags = {});

	/**
	 * @brief Creates a private lobby that any player can join. If no game-type is given, the lobby cannot provision a game server.
	 * The passcode for the lobby is of length PasscodeSize and contained in ULobby* structs for which you are the host. You can read it from ULobby::Passcode. 
	 * LobbyData is data associated to the lobby and PlayerTags are a set of non-unique Name/Value pairs associated to each player.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle CreateClosedLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers,
	                                                TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags);

	/**
	 * @copydoc CreateClosedLobbyOperation 
	 */
	FBeamOperationHandle CPP_CreateClosedLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType,
	                                                    int32 MaxPlayers = 32, TMap<FString, FString> LobbyData = {}, TArray<FBeamTag> PlayerTags = {});

	/**
	 * @brief This operation will update the KnownLobbies array with the newest ULobby data for the given LobbyId.
	 * Generally, you'll only need to call this if you are doing something custom as this system calls this whenever a notification is received about lobby changes and invokes callbacks for you.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle RefreshLobbyDataOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FGuid LobbyId);

	/**
	 * @copydoc RefreshLobbyDataOperation 
	 */
	FBeamOperationHandle CPP_RefreshLobbyDataOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FGuid LobbyId);

	/**
	 * @brief This operation will update the KnownLobbies array with the public information about existing public ULobby data that are of the given game type filter.
	 * Generally, you'll call this to show a list of public lobbies people can join and play. Try to use paging to avoid performance issues. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle RefreshLobbiesDataOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamContentId MatchTypeFilter, int32 PageStart = -1, int32 PageSize = -1);

	/**
	 * @copydoc RefreshLobbiesDataOperation 
	 */
	FBeamOperationHandle CPP_RefreshLobbiesDataOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamContentId MatchTypeFilter, int32 PageStart = -1,
	                                                     int32 PageSize = -1);

	/**
	 * @brief Join a public lobby based on its Id. PlayerTags are your initial player tags that will be shared to every other player in the lobby via server notification.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle JoinLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FGuid LobbyId, TArray<FBeamTag> PlayerTags);

	/**
	 * @copydoc JoinLobbyOperation 
	 */
	FBeamOperationHandle CPP_JoinLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FGuid LobbyId, TArray<FBeamTag> PlayerTags = {});

	/**
	 * @brief Join a private lobby based on its Passcode. PlayerTags are your initial player tags that will be shared to every other player in the lobby via server notification.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle JoinLobbyByPasscodeOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Passcode, TArray<FBeamTag> PlayerTags);

	/**
	 * @copydoc JoinLobbyByPasscodeOperation 
	 */
	FBeamOperationHandle CPP_JoinLobbyByPasscodeOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Passcode, TArray<FBeamTag> PlayerTags = {});

	/**
	 * @brief Leaves whatever lobby the given player is in.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle LeaveLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc LeaveLobbyOperation 
	 */
	FBeamOperationHandle CPP_LeaveLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief If you are the host, kicks the player with the given FBeamGamerTag from your lobby. The good ol' boot.	  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle KickPlayerOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamGamerTag Player);

	/**
	 * @copydoc KickPlayerOperation 
	 */
	FBeamOperationHandle CPP_KickPlayerOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamGamerTag Player);

private:
	// Operation Implementations
	void CreateOpenLobby(FUserSlot UserSlot, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers = 32, TMap<FString, FString> LobbyData = {}, TArray<FBeamTag> PlayerTags = {},
	                     FBeamOperationHandle Op = {});
	void CreateClosedLobby(FUserSlot UserSlot, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers = 32, TMap<FString, FString> LobbyData = {}, TArray<FBeamTag> PlayerTags = {},
	                       FBeamOperationHandle Op = {});
	void RefreshLobbyData(FUserSlot UserSlot, FGuid LobbyId, FBeamOperationHandle Op);
	void RefreshLobbiesData(FUserSlot UserSlot, FBeamContentId MatchTypeFilter, int32 PageStart = -1, int32 PageSize = -1, FBeamOperationHandle Op = {});
	void JoinLobby(FUserSlot UserSlot, FGuid LobbyId, TArray<FBeamTag> PlayerTags = {}, FBeamOperationHandle Op = {});
	void JoinLobbyByPasscode(FUserSlot UserSlot, FString Passcode, TArray<FBeamTag> PlayerTags = {}, FBeamOperationHandle Op = {});
	void LeaveLobby(FUserSlot UserSlot, FBeamOperationHandle Op);
	void KickPlayer(FUserSlot UserSlot, FBeamGamerTag Player, FBeamOperationHandle Op);

	// TODO: This needs a ProvisionGamerServerForLobby (or something along these lines) --- fails if lobby does not have a GameType.

	// Request Helper Functions
	FBeamRequestContext RequestJoin(const FUserSlot& UserSlot, FGuid LobbyId, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPutLobbyFullResponse Handler) const;
	FBeamRequestContext RequestJoinByPassword(const FUserSlot& UserSlot, FString Passcode, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPutPasscodeFullResponse Handler) const;
	FBeamRequestContext RequestGetLobby(const FUserSlot& UserSlot, FGuid LobbyId, FBeamOperationHandle Op, FOnGetLobbyFullResponse Handler) const;
	FBeamRequestContext RequestGetLobbies(const FUserSlot& UserSlot, FBeamContentId MatchTypeFilter, int32 PageStart, int32 PageSize, FBeamOperationHandle Op, FOnGetLobbiesFullResponse Handler) const;
	FBeamRequestContext RequestPostLobbies(const FUserSlot& UserSlot, FString LobbyName, FString LobbyDescription, ELobbyRestriction Restriction, FBeamContentId MatchType, int32 PasscodeLength,
	                                       int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPostLobbiesFullResponse Handler) const;
	FBeamRequestContext RequestRemoveFromLobby(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag GamerTag, FBeamOperationHandle Op, FOnDeleteLobbyFullResponse Handler) const;
	FBeamRequestContext RequestUpdateLobbyMetadata(const FUserSlot& UserSlot, FGuid LobbyId, FString LobbyName, FString LobbyDescription, ELobbyRestriction Restriction, FBeamContentId MatchType,
	                                               FBeamGamerTag NewHost, int32 MaxPlayers, TMap<FString, FString> GlobalDataUpdates, TArray<FString> GlobalDataRemove, FBeamOperationHandle Op, FOnApiLobbyPutMetadataFullResponse Handler) const;
	FBeamRequestContext RequestUpdatePlayerTag(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag PlayerId, TArray<FBeamTag> PlayerTags, bool bShouldReplace, FBeamOperationHandle Op,
	                                           FOnPutTagsFullResponse Handler) const;


	// Notification Hooks
	UFUNCTION()
	void OnLobbyUpdatedHandler(FLobbyUpdateNotificationMessage Msg, FUserSlot Slot);


	// Helper Functions
	void InitializeLobbyInfoForSlot(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser);
	void UpdateLobbyPlayerInfo(FUserSlot Slot, const ULobby* LobbyData, FDelegateHandle NewSubscriptionDelegate);
	void ReplaceOrAddKnownLobbyData(ULobby* LobbyData);
	void ClearLobbyForSlot(FUserSlot Slot);
};
