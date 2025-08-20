// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

#pragma once

#include <AutoGen/SubSystems/Lobby/ApiLobbyGetLobbiesRequest.h>
#include <AutoGen/SubSystems/Lobby/ApiLobbyPostServerByIdRequest.h>

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataByIdRequest.h"
#include "AutoGen/SubSystems/Lobby/DeleteLobbyRequest.h"
#include "AutoGen/SubSystems/Lobby/DeleteTagsRequest.h"
#include "AutoGen/SubSystems/Lobby/GetLobbyRequest.h"
#include "AutoGen/SubSystems/Lobby/PostLobbiesRequest.h"
#include "AutoGen/SubSystems/Lobby/PutLobbyRequest.h"
#include "AutoGen/SubSystems/Lobby/PutPasscodeRequest.h"
#include "AutoGen/SubSystems/Lobby/PutTagsRequest.h"
#include "BeamNotifications/SubSystems/BeamLobbyNotifications.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamLobbySubsystem.generated.h"

class UBeamLobbySubsystem;
class UBeamLobbyApi;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLobbyEventCode, const FUserSlot&, ULobby*, FLobbyUpdateNotificationMessage)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLobbyEvent, const FUserSlot&, Slot, ULobby*, Lobby, FLobbyUpdateNotificationMessage, RawEvt);

UCLASS(BlueprintType)
class UBeamLobbyState : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * User slot whose lobby state we are tracking. 
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUserSlot OwnerUserSlot;

	/**
	 * The handle for the UBeamLobbyNotifications::CPP_SubscribeToLobbyUpdate we attach to each lobby state.
	 * This is never unsubscribed.
	 */
	FDelegateHandle NotificationSubscriptionHandle;

	/**
	 * Id for the current lobby the OwnerUserSlot is in.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGuid LobbyId;

	/**
	 * GamerTag of the OwnerUserSlotPlayer.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamGamerTag OwnerGamerTag;

	/**
	 * Whether the OwnerUserSlot player is the host/owner of this lobby.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLobbyOwner;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyEvent OnLobbyJoined;
	FOnLobbyEventCode OnLobbyJoinedCode;

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

	friend bool operator==(const ULobby& Lhs, const UBeamLobbyState& RHS)
	{
		return Lhs.LobbyId.Val.Equals(RHS.LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower));
	}

	friend bool operator==(const UBeamLobbyState& Lhs, const UBeamLobbyState& RHS)
	{
		return Lhs.LobbyId == RHS.LobbyId;
	}

	friend bool operator!=(const UBeamLobbyState& Lhs, const UBeamLobbyState& RHS)
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
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGuid LobbyId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUserSlot OwnerUserSlot;

	FOptionalString NewLobbyName;
	FOptionalString NewLobbyDescription;
	FOptionalLobbyRestriction NewRestriction;
	FOptionalBeamContentId NewGameType;
	FOptionalBeamGamerTag NewHost;
	FOptionalInt32 NewMaxPlayers;

	FOptionalMapOfString GlobalDataUpdates;
	FOptionalArrayOfString GlobalDataDeletes;

	explicit UBeamLobbyUpdateCommand() = default;

	bool HasGlobalDataUpdate() const
	{
		return NewLobbyName.IsSet || NewLobbyDescription.IsSet || NewRestriction.IsSet || NewGameType.IsSet || NewHost.IsSet || NewMaxPlayers.IsSet ||
			(GlobalDataUpdates.IsSet && !GlobalDataUpdates.Val.IsEmpty()) || (GlobalDataDeletes.IsSet && !GlobalDataDeletes.Val.IsEmpty());
	}
};

USTRUCT(BlueprintType)
struct FBeamLobbyKeyPair
{
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FString> Map;

	GENERATED_BODY()
	;

	explicit FBeamLobbyKeyPair(TMap<FString, FString> Map)
		: Map(Map)
	{
	}

	FBeamLobbyKeyPair() = default;
};

/**
 * 
 */
UCLASS(BlueprintType, Config=Game)
class BEAMABLECORERUNTIME_API UBeamLobbySubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	friend class UBeamPIE;

public:
	inline static const FString Reserved_Lobby_From_Editor_Play_Mode_Property = "__beam_lobby_from_editor_play_mode_settings__";

	inline static const FString Reserved_Game_Server_Ready_Property = TEXT("__beam_game_server_ready_lobby__");
	inline static const FString Reserved_Game_Server_URL = TEXT("__beam_game_server_url_lobby__");
	inline static const FString Reserved_Game_Server_Port = TEXT("__beam_game_server_port_lobby__");

	inline static const FString Reserved_Dedicated_Server_Property = TEXT("__beam_game_server_lobby__");
	inline static const FString Reserved_Listen_Server_Property = TEXT("__beam_listen_server_lobby__");

	inline static const FString Reserved_PlayerTag_UniqueNetId_Property = TEXT("__beam_unreal_unique_net_id__");

	inline static const FString Reserved_LoginOpt_GamerTag_Required = TEXT("LogOptBeamGamerTag");
	inline static const FString Reserved_LoginOpt_AccessToken_Required = TEXT("LogOptBeamAccessToken");
	inline static const FString Reserved_LoginOpt_RefreshToken_Required = TEXT("LogOptBeamRefreshToken");
	inline static const FString Reserved_LoginOpt_ExpiresIn_Required = TEXT("LogOptBeamExpiresIn");
	inline static const FString Reserved_LoginOpt_LobbyId_Optional = TEXT("LogOptLobbyId");

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Config)
	int32 PasscodeSize;

	/**
	 * Holds information about which lobby each local player is in. 
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FUserSlot, UBeamLobbyState*> LocalPlayerLobbyInfo;

	/**
	 * Holds the Lobby objects.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<ULobby*> KnownLobbies;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FUserSlot, UBeamLobbyUpdateCommand*> UpdateCommands;

private:
	volatile int64 AutoIncrementServerMappingSlotsIdx = -1;

	/**
	 * This only ever exists in game servers that call RegisterLobbyWithServerOperation.
	 */
	TMap<FString, FBeamGamerTag> Server_NetIdToGamerTag;
	TMap<FBeamGamerTag, FString> Server_GamerTagToNetId;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamLobbySubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>(); }


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
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="UserSlot"))
	UBeamLobbyState* GetCurrentSlotLobbyState(FUserSlot Slot);

	/**
	 * Iterate over all players for a specific lobby object, it also returns a parallel list for the player properties
	 */
	void GetAllLobbyPlayers(ULobby* Lobby, TArray<ULobbyPlayer*>& Players, TArray<TMap<FString, FString>>& PlayerProperties);

	/**
	 * Iterate over all players for a specific lobby object, it also returns a parallel list for the player properties
	 * Returns false if the lobby don't exists
	 */
	bool GetAllLobbyPlayersById(FGuid LobbyId, TArray<ULobbyPlayer*>& Players, TArray<TMap<FString, FString>>& PlayerProperties);

	/*
	 * Tries to get the current lobby passcode for a user slot
	 * returns false if the user is not in a lobby or if it doesn't have a pass code.
	 */
	UFUNCTION(Blueprintable)
	bool TryGetCurrentSlotPasscode(FUserSlot Slot, FString& Passcode);

	/**
	 * Tries to get whatever the current local data for the given lobby id is. If you want a guarantee that this data is up-to-date call, [CPP_]RefreshLobbyOperation first.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLobbyById(FGuid LobbyId, ULobby*& Lobby);

	/**
	 * Gets the current LobbyId for a give slot. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetCurrentLobbyId(FUserSlot Slot, FGuid& LobbyId);

	/**
	 * Tries to get whatever the current local data for the given user slot's current lobby. If you want a guarantee that this data is up-to-date call, [CPP_]RefreshLobbyOperation first.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetCurrentLobby(FUserSlot Slot, ULobby*& Lobby);

	/**
	 *  Try to get a specific data from a ULobby* Object.
	 *  The default value is what will be return in case of it fail to get the value.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetGlobalLobbyData(ULobby* Lobby, FString DataKey, FString DefaultValue, FString& GlobalData);

	/**
	 *  Try to get a specific json data from a ULobby* Object and cast it to selected type.
	 *  The default value is what will be return in case of it fail to get the value.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetGlobalLobbyDataCasted(ULobby* Lobby, FString DataKey, UPARAM(meta=(MustImplement = "BeamJsonSerializableUObject", BeamCastType))
	                                 TSubclassOf<UObject> CastTarget,
	                                 UPARAM(meta=(MustImplement = "BeamJsonSerializableUObject"))
	                                 UObject* DefaultValue, UPARAM(meta=(BeamCastTarget))
	                                 UObject*& GlobalData);

	/**
	 *  It will return the global data from a ULobby* Object as parallel lists of keys and values.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllLobbyGlobalData(ULobby* Lobby, TArray<FString>& Keys, TArray<FString>& Values);

	/*
	 * Get a player data property for a specific player
	 * Returns false if this property don't exists
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLobbyPlayerData(ULobby* Lobby, FBeamGamerTag PlayerGamerTag, FString DataKey, FString DefaultValue, FString& PlayerData);

	/**
	 *  Try a player data property for a specific player and cast it to selected type.
	 *  The default value is what will be return in case of it fail to get the value.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLobbyPlayerDataCasted(ULobby* Lobby, FBeamGamerTag PlayerGamerTag, UPARAM(meta=(MustImplement = "BeamJsonSerializableUObject", BeamCastType))
	                                 TSubclassOf<UObject> CastTarget, FString DataKey,
	                                 UPARAM(meta=(MustImplement = "BeamJsonSerializableUObject"))
	                                 UObject* DefaultValue, UPARAM(meta=(BeamCastTarget))
	                                 UObject*& PlayerData);

	/**
	 *  It will return the a specific player data from a ULobby* Object as parallel lists of keys and values.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllLobbyPlayerData(ULobby* Lobby, FBeamGamerTag PlayerGamerTag, TArray<FString>& Keys, TArray<FString>& Values);

	/**
	 *  Try to get a specific data from a ULobby* Object using the lobby id.
	 *  The default value is what will be return in case of it fail to get the value.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetGlobalLobbyDataById(FGuid LobbyId, FString DataKey, FString DefaultValue, FString& GlobalData);

	/**
	 *  It will return the global data from a ULobby* Object as parallel lists of keys and values.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetAllLobbyGlobalDataById(FGuid LobbyId, TArray<FString>& Keys, TArray<FString>& Values);

	/**
	 * Get a player data property for a specific player
	 * Returns false if this property don't exists
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLobbyPlayerDataById(FGuid LobbyId, FBeamGamerTag PlayerGamerTag, FString DataKey, FString DefaultValue, FString& PlayerData);

	/**
	 *  It will return the a specific player data from a ULobby* Object as parallel lists of keys and values.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetAllLobbyPlayerDataById(FGuid LobbyId, FBeamGamerTag PlayerGamerTag, TArray<FString>& Keys, TArray<FString>& Values);

	/**
	 * Return a list with all lobbies and a parallel list with the lobby global data.
	 */
	UFUNCTION(BlueprintCallable)
	void GetAllLobbies(TArray<ULobby*>& Lobbies, TArray<FBeamLobbyKeyPair>& GlobalData);

	/**
	 * Tries to get whatever the current local data for the given user slot's current lobby state. If you want a guarantee that this data is up-to-date call, [CPP_]RefreshLobbyOperation first.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetCurrentLobbyState(FUserSlot Slot, UBeamLobbyState*& Lobby);

	/**
	 * Call this to begin building a set of batched updates to a lobby the player is in.
	 * After this call, use the various PrepareUpdate______ functions to build out the update.
	 * Finally, run the CommitLobbyUpdateOperation to submit the lobby changes.
	 *
	 * When bForce is on, it'll discard any update that was previously being constructed before starting a new one. Otherwise, it'll return false. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryBeginUpdateLobby(FUserSlot Slot, bool bForce);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the new name for the lobby.
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateName(const FUserSlot& Slot, const FString& NewName);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the new description for the lobby.
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateDescription(FUserSlot Slot, const FString& NewDesc);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the new restriction for the lobby.
	 * A passcode will be generated by going from Public->Private.
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateRestriction(FUserSlot Slot, const EBeamLobbyRestriction& NewLobbyRestriction);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the new UBeamGameTypeContent (or subclass) for the lobby.	 
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateGameType(FUserSlot Slot, const FBeamContentId& NewGameType);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the new host for the lobby. Must be one of the players in the lobby.	 
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateHost(FUserSlot Slot, const FBeamGamerTag& NewHost);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the new MaxPlayer count for the lobby.	 
	 * Will fail if you are not the lobby host or if there are more players in the lobby than the new max players.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateMaxPlayers(FUserSlot Slot, const int32& NewMaxPlayers);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the which entries in ULobby::Data should added or updated in the lobby.	 
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareUpdateGlobalData(FUserSlot Slot, const TMap<FString, FString>& UpdatedGlobalData);

	/**
	 * After calling TryBeginUpdateLobbyData, call this to set the which entries in ULobby::Data should be removed from the lobby.	 
	 * Will fail if you are not the lobby host.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareDeleteGlobalData(FUserSlot Slot, const TArray<FString>& GlobalDataToRemove);

	/**
	 *  If a lobby has information in its @link ULobby::Data @endlink map for a URL and Port, you can use this node to call OpenLevel with that information in the lobby.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue", AdvancedDisplay="UrlKey,PortKey,AdditionalOptions"))
	bool TryOpenLevelFromLobby(FUserSlot Slot, FString UrlKey = TEXT(""), FString PortKey = TEXT(""), FString AdditionalOptions = TEXT(""));

	/**
	 * Use this to create to add to an OpenLevel URL all the options required to use CPP_AcceptUserIntoGameServerOperation in your UGameModeBase::PreLoginAsync call. 
	 */
	UFUNCTION(BlueprintCallable)
	FString PrepareLoginOptions(const FUserSlot& Slot, const FString Options);

	/**
	 * @copybrief PrepareLoginOptions
	 */
	UFUNCTION(BlueprintCallable)
	FString PrepareLoginOptionsByLocalPlayer(const ULocalPlayer* LocalPlayer, const FString Options);

	/**
	 * @copybrief PrepareLoginOptions
	 */
	UFUNCTION(BlueprintCallable)
	FString PrepareLoginOptionsByPlayerController(const AController* Controller, const FString Options);

	/**
	 * @copybrief PrepareLoginOptions
	 */
	UFUNCTION(BlueprintCallable)
	FString PrepareLoginOptionsByLocalPlayerIndex(int32 LocalPlayerIdx, const FString Options);

	/**
	 * @copybrief PrepareLoginOptions
	 */
	UFUNCTION(BlueprintCallable)
	FString PrepareLoginOptionsFull(const FString& Options, const FString& AccessToken, const FString& RefreshToken, int64 ExpiresIn, const FBeamGamerTag& GamerTag, FString LobbyId) const;

	/**
	 * For integration with other implementations of Unreal's Gameplay Framework.
	 *
	 * In the client, this maps the UE's LocalPlayerIndex to the array of @link UBeamCoreSettings::RuntimeUserSlots @endlink.
	 * In dedicated servers, we map the UE's a controller's APlayerState's UniqueNetId to a user in a Lobby. This mapping is used to find the PlayerController for the given GamerTag.	 
	 *	 
	 * In all failure cases, this returns an empty @link FBeamGamerTag @endlink 
	 */
	UFUNCTION(BlueprintCallable)
	APlayerController* GetPlayerControllerByGamerTag(FBeamGamerTag GamerTag);

	/**
	 * For integration with other implementations of Unreal's Gameplay Framework.
	 *
	 * In the client, this maps the UE's LocalPlayerIndex to the array of @link UBeamCoreSettings::RuntimeUserSlots @endlink.
	 * In dedicated servers, this maps the UE's a controller's APlayerState's UniqueNetId to a user in a Lobby.
	 * Then, it maps that user to a @link FUserSlot @endlink if you have called @link UBeamLobbySubsystem::AcceptUserIntoGameServer @endlink.
	 *
	 * These are not available unless you are using @link UBeamLobbySubsystem::AcceptUserIntoGameServer @endlink.
	 *
	 * In all failure cases, this returns an empty @link FUserSlot @endlink 
	 */
	UFUNCTION(BlueprintCallable)
	FUserSlot GetUserSlotByPlayerController(const AController* Controller);

	/**
	 * @copybrief GetUserSlotByPlayerController
	 */
	UFUNCTION(BlueprintCallable)
	FUserSlot GetUserSlotByPlayerState(const APlayerState* State);

	/**
	 * For integration with other implementations of Unreal's Gameplay Framework.
	 *
	 * In the client, this maps the UE's LocalPlayerIndex to the array of @link UBeamCoreSettings::RuntimeUserSlots @endlink. This returns an empty Gamertag if the user is not authenticated.
	 *
	 * In dedicated servers, this maps the UE's a controller's APlayerState's UniqueNetId to a user in a Lobby. Will only return valid values AFTER AGameMode::OnPostLogin.
	 * If @link UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds @endlink is true, this will just get the gamertag from it.
	 * This returns an empty GamerTag if the user was not accepted into the game server yet.
	 */
	UFUNCTION(BlueprintCallable)
	FBeamGamerTag GetGamerTagByPlayerController(const AController* Controller);
	/**
	 * @copybrief GetGamerTagByPlayerState
	 */
	UFUNCTION(BlueprintCallable)
	FBeamGamerTag GetGamerTagByPlayerState(const APlayerState* State);

	/**
	 * Iterates over the list of lobbies we are managing and find the one that has this player.
	 */
	UFUNCTION(BlueprintCallable)
	FGuid GetLobbyIdByGamerTag(FBeamGamerTag GamerTag);


	// LOCAL STATE - Dedicated Server

	/**
	 * Parses the CLArgs for the "BeamableDedicatedServerInstanceLobbyId" for this process.
	 * If it fails to find it, falls back to the "BEAMABLE_DEDICATED_SERVER_INSTANCE_LOBBY_ID" env-arg.
	 *
	 * Logs out a warning if neither are present.
	 */
	UFUNCTION(BlueprintCallable)
	FGuid GetLobbyIdFromCLArgs();

	/**
	 * You should only ever use this if you are running a single Lobby/Match per instance.
	 * If you are running multiples, call TryGetLobby with the id of the lobby you want.
	 * 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetDedicatedServerInstanceLobby(ULobby*& Lobby);

	// OPERATIONS

	/**
	 * @brief Creates a public lobby that any player can join. If no game-type is given, the lobby cannot provision a game server.
	 * LobbyData is data associated to the lobby and PlayerTags are a set of non-unique Name/Value pairs associated to each player.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle CreateOpenLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Name, FString Desc, UPARAM(meta=(BeamFilter="game_types"))
	                                              FBeamContentId MatchType,
	                                              int32 MaxPlayers, TMap<FString, FString> LobbyData,
	                                              TArray<FBeamTag> PlayerTags);

	/**
	 * @copydoc CreateOpenLobbyOperation 
	 */
	FBeamOperationHandle CPP_CreateOpenLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Name, FString Desc, UPARAM(meta=(BeamFilter="game_types"))
	                                                  FBeamContentId MatchType,
	                                                  int32 MaxPlayers = 32,
	                                                  TMap<FString, FString> LobbyData = {},
	                                                  TArray<FBeamTag> PlayerTags = {});

	/**
	 * @brief Creates a private lobby that any player can join. If no game-type is given, the lobby cannot provision a game server.
	 * The passcode for the lobby is of length PasscodeSize and contained in ULobby* structs for which you are the host. You can read it from ULobby::Passcode. 
	 * LobbyData is data associated to the lobby and PlayerTags are a set of non-unique Name/Value pairs associated to each player.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle CreateClosedLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Name, FString Desc, UPARAM(meta=(BeamFilter="game_types"))
	                                                FBeamContentId MatchType,
	                                                int32 MaxPlayers,
	                                                TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags);

	/**
	 * @copydoc CreateClosedLobbyOperation 
	 */
	FBeamOperationHandle CPP_CreateClosedLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Name, FString Desc, UPARAM(meta=(BeamFilter="game_types"))
	                                                    FBeamContentId MatchType,
	                                                    int32 MaxPlayers = 32,
	                                                    TMap<FString, FString> LobbyData = {},
	                                                    TArray<FBeamTag> PlayerTags = {});

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
	FBeamOperationHandle RefreshLobbiesDataOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UPARAM(meta=(BeamFilter="game_types"))
	                                                 FBeamContentId MatchTypeFilter, int32 PageStart = -1,
	                                                 int32 PageSize = -1);

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

	/**
	 * @brief If you are the host, you are allowed to make changes to the lobby metadata.
	 *
	 * You can modify lobby configuration as well as add new global key-value data that'll be propagated to all other clients.
	 * See TryBeginUpdateLobbyData and other Prepare[Update|Delete] functions
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle CommitLobbyUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CommitLobbyUpdateOperation 
	 */
	FBeamOperationHandle CPP_CommitLobbyUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief You can update your own player data when you are inside the lobby. You can update any player's tags if you are the host.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle UpdatePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdatePlayerDataOperation 
	 */
	FBeamOperationHandle CPP_UpdatePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief You can update your own player data when you are inside the lobby.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle UpdateSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdateSlotPlayerDataOperation 
	 */
	FBeamOperationHandle CPP_UpdateSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief You can delete any player's tags if you are the host.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle DeletePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc DeletePlayerDataOperation 
	 */
	FBeamOperationHandle CPP_DeletePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief You can delete your own player tags when you are inside the lobby.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle DeleteSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc DeleteSlotPlayerDataOperation 
	 */
	FBeamOperationHandle CPP_DeleteSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief You can delete your own player tags when you are inside the lobby.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby", meta=(AutoCreateRefTerm="NewGameType"))
	FBeamOperationHandle ProvisionGameServerForLobbyOperation(FUserSlot UserSlot, FOptionalBeamContentId NewGameType, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc ProvisionGameServerForLobbyOperation 
	 */
	FBeamOperationHandle CPP_ProvisionGameServerForLobbyOperation(FUserSlot UserSlot, FOptionalBeamContentId NewGameType, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief From a dedicated server OR if you are the lobby host, you can update the global data when you are inside the lobby.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby")
	FBeamOperationHandle UpdateGlobalDataOperation(FUserSlot UserSlot, const FGuid& LobbyId, TMap<FString, FString> ToUpdate, TArray<FString> ToDelete, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdateGlobalDataOperation 
	 */
	FBeamOperationHandle CPP_UpdateGlobalDataOperation(FUserSlot UserSlot, const FGuid& LobbyId, TMap<FString, FString> ToUpdate, TArray<FString> ToDelete, FBeamOperationEventHandlerCode OnOperationEvent);

	// OPERATIONS - Dedicated Server
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby", meta=(AutoCreateRefTerm="NewGameType"))
	FBeamOperationHandle RegisterLobbyWithServerOperation(FUserSlot UserSlot, const FGuid& LobbyId, FBeamOperationEventHandler OnOperationEvent);

	FBeamOperationHandle CPP_RegisterLobbyWithServerOperation(FUserSlot UserSlot, const FGuid& LobbyId, FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby", meta=(AutoCreateRefTerm="NewGameType"))
	FBeamOperationHandle NotifyLobbyReadyForClientsOperation(FUserSlot UserSlot, const FGuid& LobbyId, FBeamOperationEventHandler OnOperationEvent);

	FBeamOperationHandle CPP_NotifyLobbyReadyForClientsOperation(FUserSlot UserSlot, const FGuid& LobbyId, FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Lobby", meta=(AutoCreateRefTerm="NewGameType"))
	FBeamOperationHandle AcceptUserIntoGameServerOperation(FUserSlot UserSlot, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FBeamOperationEventHandler OnOperationEvent);

	FBeamOperationHandle CPP_AcceptUserIntoGameServerOperation(FUserSlot UserSlot, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FBeamOperationEventHandlerCode OnOperationEvent);

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
	void CommitLobbyUpdate(const FUserSlot& Slot, FBeamOperationHandle Op);
	void UpdatePlayerTags(const FUserSlot& Slot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, bool bShouldReplaceRepeatedTags, FBeamOperationHandle Op);
	void DeletePlayerTags(const FUserSlot& Slot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationHandle Op);
	void ProvisionGameServerForLobby(const FUserSlot& Slot, FOptionalBeamContentId NewGameContent, FBeamOperationHandle Op);
	void UpdateGlobalData(FUserSlot Slot, const FGuid& LobbyId, TMap<FString, FString> ToUpdate, TArray<FString> ToDelete, FBeamOperationHandle Op);

	// Dedicated Server API
	void RegisterLobbyWithServer(const FUserSlot& Slot, const FGuid& LobbyId, FBeamOperationHandle Op);
	void AcceptUserIntoGameServer(const FUserSlot& Slot, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FBeamOperationHandle Op);

	// Request Helper Functions
	FBeamRequestContext RequestJoin(const FUserSlot& UserSlot, FGuid LobbyId, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPutLobbyFullResponse Handler) const;
	FBeamRequestContext RequestJoinByPassword(const FUserSlot& UserSlot, FString Passcode, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPutPasscodeFullResponse Handler) const;
	FBeamRequestContext RequestGetLobby(const FUserSlot& UserSlot, FGuid LobbyId, FBeamOperationHandle Op, FOnGetLobbyFullResponse Handler) const;
	FBeamRequestContext RequestGetLobbies(const FUserSlot& UserSlot, FBeamContentId MatchTypeFilter, int32 PageStart, int32 PageSize, FBeamOperationHandle Op, FOnApiLobbyGetLobbiesFullResponse Handler) const;
	FBeamRequestContext RequestPostLobbies(const FUserSlot& UserSlot, FString LobbyName, FString LobbyDescription, EBeamLobbyRestriction Restriction, FBeamContentId MatchType, int32 PasscodeLength,
	                                       int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPostLobbiesFullResponse Handler) const;
	FBeamRequestContext RequestRemoveFromLobby(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag GamerTag, FBeamOperationHandle Op, FOnDeleteLobbyFullResponse Handler) const;
	FBeamRequestContext RequestUpdateLobbyMetadata(const FUserSlot& UserSlot, FGuid LobbyId, FOptionalString LobbyName, FOptionalString LobbyDescription, FOptionalLobbyRestriction Restriction,
	                                               FOptionalBeamContentId MatchType, FOptionalBeamGamerTag NewHost, FOptionalInt32 MaxPlayers, FOptionalMapOfString GlobalDataUpdates,
	                                               FOptionalArrayOfString GlobalDataDeletes, FBeamOperationHandle Op, FOnApiLobbyPutMetadataByIdFullResponse Handler) const;
	FBeamRequestContext RequestUpdatePlayerTag(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag PlayerId, TArray<FBeamTag> PlayerTags, bool bShouldReplace, FBeamOperationHandle Op,
	                                           FOnPutTagsFullResponse Handler) const;
	FBeamRequestContext RequestDeletePlayerTags(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag PlayerId, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op,
	                                            FOnDeleteTagsFullResponse Handler) const;
	FBeamRequestContext RequestPostServer(const FUserSlot& UserSlot, FGuid LobbyId, FOptionalBeamContentId SelectedMatchType, FBeamOperationHandle Op, FOnApiLobbyPostServerByIdFullResponse Handler) const;


	// Notification Hooks
	UFUNCTION()
	void OnLobbyUpdatedHandler(FLobbyUpdateNotificationMessage Msg, FUserSlot Slot);


	// Helper Functions
	void InitializeLobbyInfoForSlot(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser);
	void UpdateLobbyPlayerInfo(FUserSlot Slot, const ULobby* LobbyData);
	void ReplaceOrAddKnownLobbyData(ULobby* LobbyData);
	void ClearLobbyForSlot(FUserSlot Slot);

	bool GuardSlotIsInLobby(const FUserSlot& Slot, UBeamLobbyState*& LobbyState);
	bool GuardIsLobbyOwner(const FUserSlot& Slot, UBeamLobbyState* LobbyState);
	bool GuardUpdateCommandBegun(const FUserSlot& Slot);
};
