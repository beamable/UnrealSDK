// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================


#include "Subsystems/Lobby/BeamLobbySubsystem.h"

#include "AutoGen/Optionals/OptionalArrayOfLobbyLibrary.h"
#include "AutoGen/SubSystems/BeamLobbyApi.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

void UBeamLobbySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UserSlots = Runtime->UserSlotSystem;
	RequestTracker = Runtime->RequestTrackerSystem;
	LobbyApi = GEngine->GetEngineSubsystem<UBeamLobbyApi>();
	LobbyNotification = GEngine->GetEngineSubsystem<UBeamLobbyNotifications>();
}

void UBeamLobbySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBeamLobbySubsystem::OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp)
{
	// If we are running a dedicated server...
	if (IsRunningDedicatedServer())
	{
		//... that expects to run a single lobby's match (we expect either a CLArg or a EnvVar to exist)
		FString LobbyIdStr;
		if (!FParse::Value(FCommandLine::Get(), TEXT("BeamableDedicatedServerInstanceLobbyId="), LobbyIdStr))
		{
			LobbyIdStr = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_DEDICATED_SERVER_INSTANCE_LOBBY_ID"));
		}

		// If no CLArg or EnvVar are provided, we assume the user will run multiple matches per server and will make the calls to RefreshLobbyDataOperation from their integration with their game server orchestrator
		// (Hathora, GameLift, etc...)
		if (LobbyIdStr.IsEmpty())
		{
			UE_LOG(LogBeamLobby, Display, TEXT("No LobbyId was provided to this dedicated server instance. "
				       "To fetch lobby data, register a call to OnBeamableStarted and then make requests as needed. "
				       "Otherwise, use either a CLArg or an EnvVar to pass in the LobbyId and we'll prefetch it for you. "
				       "If you are running multiple lobbies/rooms/games/matches in one server instance, we cannot prefetch for you. "
				       "Instead, you should make the calls to RefreshLobbyDataOperation as new matches are assigned to this server instance by your game server orchestrator provider."))

			DedicatedServerInstanceLobbyId.Invalidate();
			Super::OnBeamableStarting_Implementation(ResultOp);
		}
		// Otherwise, we can prefetch the Lobby information for this instance
		else
		{
			DedicatedServerInstanceLobbyId = FGuid(LobbyIdStr);
			ResultOp = RefreshLobbyDataOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), {}, DedicatedServerInstanceLobbyId);
		}
	}
	else
	{
		DedicatedServerInstanceLobbyId.Invalidate();
		Super::OnBeamableStarting_Implementation(ResultOp);
	}
}

void UBeamLobbySubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	// Initialize the dictionary of lobby information for this signed in player.
	InitializeLobbyInfoForSlot(UserSlot, BeamRealmUser);
	Super::OnUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);
}

void UBeamLobbySubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	// Clear the Lobby Information for this local player.
	LocalPlayerLobbyInfo.Remove(UserSlot);

	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}


// LOCAL STATE

ULobby* UBeamLobbySubsystem::GetCurrentLobby(const FUserSlot& UserSlot)
{
	const auto Slot = UserSlot.Name.IsEmpty() ? GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot() : UserSlot;
	const auto UserLobbyInfo = LocalPlayerLobbyInfo[Slot];

	if (const auto LobbyPtr = KnownLobbies.FindByPredicate([UserLobbyInfo](const ULobby* L) { return *L == *UserLobbyInfo; }))
		return *LobbyPtr;

	checkf(false, TEXT("Ensure you only call this when the user is in a lobby."))
	return nullptr;
}

UBeamLobbyState* UBeamLobbySubsystem::GetCurrentSlotLobbyState(FUserSlot Slot)
{
#if WITH_TESTS
	if (Slot.Name.Contains("Test"))
	{
		FBeamRealmUser RealmUser;
		if (UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
		{
			InitializeLobbyInfoForSlot(Slot, RealmUser);
		}
	}
#endif
	UBeamLobbyState* Lobby = LocalPlayerLobbyInfo.FindChecked(Slot);
	return Lobby;
}

bool UBeamLobbySubsystem::TryGetLobbyById(FGuid LobbyId, ULobby*& Lobby)
{
	if (const auto ExistingLobbyIdx = KnownLobbies.IndexOfByPredicate([LobbyId](const ULobby* Lob) { return Lob->LobbyId.Val == LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower); });
		ExistingLobbyIdx != INDEX_NONE)
	{
		Lobby = KnownLobbies[ExistingLobbyIdx];
		return true;
	}
	Lobby = nullptr;
	return false;
}

bool UBeamLobbySubsystem::TryGetCurrentLobby(FUserSlot Slot, ULobby*& Lobby)
{
	UBeamLobbyState* LobbyState;
	if (TryGetCurrentLobbyState(Slot, LobbyState))
	{
		Lobby = GetCurrentLobby(Slot);
		return true;
	}

	Lobby = nullptr;
	return false;
}


bool UBeamLobbySubsystem::TryGetGlobalLobbyData(ULobby* Lobby, FString DataKey, FString DefaultValue, FString& GlobalData)
{
	GlobalData = DefaultValue;

	if (!Lobby || !Lobby->Data.IsSet)
	{
		return false;
	}

	if (!Lobby->Data.Val.Contains(DataKey))
	{
		return false;
	}

	GlobalData = Lobby->Data.Val[DataKey];

	return true;
}

bool UBeamLobbySubsystem::GetAllLobbyGlobalData(ULobby* Lobby, TArray<FString>& Keys, TArray<FString>& Values)
{
	Keys.Reset();
	Values.Reset();

	if (!Lobby || !Lobby->Data.IsSet)
	{
		return false;
	}

	for (auto LobbyData : Lobby->Data.Val)
	{
		Keys.Add(LobbyData.Key);
		Values.Add(LobbyData.Value);
	}

	return true;
}

bool UBeamLobbySubsystem::TryGetLobbyPlayerData(ULobby* Lobby, FBeamGamerTag PlayerGamerTag, FString DataKey, FString DefaultValue, FString& PlayerData)
{
	PlayerData = DefaultValue;

	if (!Lobby)
	{
		return false;
	}

	if (Lobby->Players.IsSet)
	{
		for (auto PlayerLobby : Lobby->Players.Val)
		{
			if (PlayerLobby->PlayerId.Val == PlayerGamerTag)
			{
				if (PlayerLobby->Tags.IsSet)
				{
					for (auto BeamTag : PlayerLobby->Tags.Val)
					{
						if (BeamTag.Name.Val == DataKey)
						{
							PlayerData = BeamTag.Value.Val;
							return true;
						}
					}
				}
				// If the tag is not set then return false
				return false;
			}
		}
	}
	return false;
}

bool UBeamLobbySubsystem::GetAllLobbyPlayerData(ULobby* Lobby, FBeamGamerTag PlayerGamerTag, TArray<FString>& Keys, TArray<FString>& Values)
{
	Keys.Reset();
	Values.Reset();

	if (!Lobby || !Lobby->Data.IsSet)
	{
		return false;
	}

	if (Lobby->Players.IsSet)
	{
		for (auto PlayerLobby : Lobby->Players.Val)
		{
			if (PlayerLobby->PlayerId.Val == PlayerGamerTag)
			{
				if (PlayerLobby->Tags.IsSet)
				{
					for (auto BeamTag : PlayerLobby->Tags.Val)
					{
						Keys.Add(BeamTag.Name.Val);
						Values.Add(BeamTag.Value.Val);
					}
					return true;
				}
				// If the tag is not set then return false
				return false;
			}
		}
	}
	return false;
}

bool UBeamLobbySubsystem::TryGetGlobalLobbyDataById(FGuid LobbyId, FString DataKey, FString DefaultValue, FString& GlobalData)
{
	ULobby* Lobby;
	TryGetLobbyById(LobbyId, Lobby);

	return TryGetGlobalLobbyData(Lobby, DataKey, DefaultValue, GlobalData);
}

bool UBeamLobbySubsystem::GetAllLobbyGlobalDataById(FGuid LobbyId, TArray<FString>& Keys, TArray<FString>& Values)
{
	ULobby* Lobby;
	TryGetLobbyById(LobbyId, Lobby);

	return GetAllLobbyGlobalData(Lobby, Keys, Values);
}

bool UBeamLobbySubsystem::TryGetLobbyPlayerDataById(FGuid LobbyId, FBeamGamerTag PlayerGamerTag, FString DataKey, FString DefaultValue, FString& PlayerData)
{
	ULobby* Lobby;
	TryGetLobbyById(LobbyId, Lobby);

	return TryGetLobbyPlayerData(Lobby, PlayerGamerTag, DataKey, DefaultValue, PlayerData);
}

bool UBeamLobbySubsystem::GetAllLobbyPlayerDataById(FGuid LobbyId, FBeamGamerTag PlayerGamerTag, TArray<FString>& Keys, TArray<FString>& Values)
{
	ULobby* Lobby;
	TryGetLobbyById(LobbyId, Lobby);

	return GetAllLobbyPlayerData(Lobby, PlayerGamerTag, Keys, Values);
}

bool UBeamLobbySubsystem::TryGetCurrentLobbyState(FUserSlot Slot, UBeamLobbyState*& Lobby)
{
	Lobby = LocalPlayerLobbyInfo.FindChecked(Slot);
	if (Lobby->LobbyId.IsValid()) return true;
	return false;
}

bool UBeamLobbySubsystem::TryGetDedicatedServerInstanceLobby(ULobby*& Lobby)
{
	check(IsRunningDedicatedServer());
	check(DedicatedServerInstanceLobbyId.IsValid())

	return TryGetLobbyById(DedicatedServerInstanceLobbyId, Lobby);
}

bool UBeamLobbySubsystem::TryBeginUpdateLobby(FUserSlot Slot, bool bForce)
{
	UBeamLobbyState* LobbyState;
	if (!TryGetCurrentLobbyState(Slot, LobbyState))
	{
		UE_LOG(LogBeamLobby, Error, TEXT("User at this slot is not in a lobby (locally). USER_SLOT=%s"), *Slot.Name)
		return false;
	}

	if (UpdateCommands.Contains(Slot) && !bForce)
	{
		UE_LOG(LogBeamLobby, Verbose, TEXT("User at this slot is not in a lobby (locally). USER_SLOT=%s"), *Slot.Name)
		return false;
	}

	UpdateCommands.Add(Slot, NewObject<UBeamLobbyUpdateCommand>());
	UpdateCommands[Slot]->OwnerUserSlot = Slot;
	UpdateCommands[Slot]->LobbyId = LobbyState->LobbyId;
	UE_LOG(LogBeamLobby, Verbose, TEXT("User at this slot started building a set of updates to the game lobby. USER_SLOT=%s"), *Slot.Name)
	return true;
}

void UBeamLobbySubsystem::PrepareUpdateName(const FUserSlot& Slot, const FString& NewName)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->NewLobbyName = FOptionalString(NewName);
}

void UBeamLobbySubsystem::PrepareUpdateDescription(FUserSlot Slot, const FString& NewDesc)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->NewLobbyDescription = FOptionalString(NewDesc);
}

void UBeamLobbySubsystem::PrepareUpdateRestriction(FUserSlot Slot, const EBeamLobbyRestriction& NewLobbyRestriction)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->NewRestriction = FOptionalLobbyRestriction(NewLobbyRestriction);
}

void UBeamLobbySubsystem::PrepareUpdateGameType(FUserSlot Slot, const FBeamContentId& NewGameType)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->NewGameType = FOptionalBeamContentId(NewGameType);
}

void UBeamLobbySubsystem::PrepareUpdateHost(FUserSlot Slot, const FBeamGamerTag& NewHost)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->NewHost = FOptionalBeamGamerTag(NewHost);
}

void UBeamLobbySubsystem::PrepareUpdateMaxPlayers(FUserSlot Slot, const int32& NewMaxPlayers)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->NewMaxPlayers = FOptionalInt32(NewMaxPlayers);
}

void UBeamLobbySubsystem::PrepareUpdateGlobalData(FUserSlot Slot, const TMap<FString, FString>& UpdatedGlobalData)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->GlobalDataUpdates = FOptionalMapOfString(UpdatedGlobalData);
}

void UBeamLobbySubsystem::PrepareDeleteGlobalData(FUserSlot Slot, const TArray<FString>& GlobalDataToRemove)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState)) return;
	if (!GuardUpdateCommandBegun(Slot)) return;
	if (!GuardIsLobbyOwner(Slot, LobbyState)) return;

	UpdateCommands[Slot]->GlobalDataDeletes = FOptionalArrayOfString(GlobalDataToRemove);
}


// OPERATIONS

FBeamOperationHandle UBeamLobbySubsystem::CreateOpenLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType,
                                                                   int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateOpenLobby(UserSlot, Name, Desc, MatchType, MaxPlayers, LobbyData, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_CreateOpenLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType,
                                                                       int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateOpenLobby(UserSlot, Name, Desc, MatchType, MaxPlayers, LobbyData, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CreateClosedLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType,
                                                                     int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateClosedLobby(UserSlot, Name, Desc, MatchType, MaxPlayers, LobbyData, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_CreateClosedLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Name, FString Desc, FBeamContentId MatchType,
                                                                         int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateClosedLobby(UserSlot, Name, Desc, MatchType, MaxPlayers, LobbyData, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::RefreshLobbyDataOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FGuid LobbyId)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshLobbyData(UserSlot, LobbyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_RefreshLobbyDataOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FGuid LobbyId)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshLobbyData(UserSlot, LobbyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::RefreshLobbiesDataOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamContentId MatchTypeFilter, int32 PageStart, int32 PageSize)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshLobbiesData(UserSlot, MatchTypeFilter, PageStart, PageSize, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_RefreshLobbiesDataOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamContentId MatchTypeFilter, int32 PageStart,
                                                                          int32 PageSize)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshLobbiesData(UserSlot, MatchTypeFilter, PageStart, PageSize, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::JoinLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FGuid LobbyId, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	JoinLobby(UserSlot, LobbyId, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_JoinLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FGuid LobbyId, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	JoinLobby(UserSlot, LobbyId, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::JoinLobbyByPasscodeOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FString Passcode, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	JoinLobbyByPasscode(UserSlot, Passcode, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_JoinLobbyByPasscodeOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FString Passcode, TArray<FBeamTag> PlayerTags)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	JoinLobbyByPasscode(UserSlot, Passcode, PlayerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::LeaveLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LeaveLobby(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_LeaveLobbyOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LeaveLobby(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::KickPlayerOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamGamerTag Player)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	KickPlayer(UserSlot, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_KickPlayerOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamGamerTag Player)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	KickPlayer(UserSlot, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CommitLobbyUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitLobbyUpdate(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_CommitLobbyUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitLobbyUpdate(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::UpdatePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);


	UpdatePlayerTags(UserSlot, TargetPlayer, Tags, true, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_UpdatePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdatePlayerTags(UserSlot, TargetPlayer, Tags, true, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::UpdateSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FBeamRealmUser SlotUser;
	if (UserSlots->GetUserDataAtSlot(UserSlot, SlotUser, this))
	{
		UpdatePlayerTags(UserSlot, SlotUser.GamerTag, Tags, true, Handle);
	}
	else
	{
		RequestTracker->TriggerOperationError(Handle, FString("NOT_SIGNED_IN"));
	}
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_UpdateSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FBeamRealmUser SlotUser;
	if (UserSlots->GetUserDataAtSlot(UserSlot, SlotUser, this))
	{
		UpdatePlayerTags(UserSlot, SlotUser.GamerTag, Tags, true, Handle);
	}
	else
	{
		RequestTracker->TriggerOperationError(Handle, FString("NOT_SIGNED_IN"));
	}
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::DeletePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);


	DeletePlayerTags(UserSlot, TargetPlayer, Tags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_DeletePlayerDataOperation(FUserSlot UserSlot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DeletePlayerTags(UserSlot, TargetPlayer, Tags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::DeleteSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FBeamRealmUser SlotUser;
	if (UserSlots->GetUserDataAtSlot(UserSlot, SlotUser, this))
	{
		DeletePlayerTags(UserSlot, SlotUser.GamerTag, Tags, Handle);
	}
	else
	{
		RequestTracker->TriggerOperationError(Handle, FString("NOT_SIGNED_IN"));
	}
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_DeleteSlotPlayerDataOperation(FUserSlot UserSlot, TArray<FBeamTag> Tags, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FBeamRealmUser SlotUser;
	if (UserSlots->GetUserDataAtSlot(UserSlot, SlotUser, this))
	{
		DeletePlayerTags(UserSlot, SlotUser.GamerTag, Tags, Handle);
	}
	else
	{
		RequestTracker->TriggerOperationError(Handle, FString("NOT_SIGNED_IN"));
	}
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::ProvisionGameServerForLobbyOperation(FUserSlot UserSlot, FOptionalBeamContentId NewGameType, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FBeamRealmUser SlotUser;
	if (UserSlots->GetUserDataAtSlot(UserSlot, SlotUser, this))
	{
		ProvisionGameServerForLobby(UserSlot, NewGameType, Handle);
	}
	else
	{
		RequestTracker->TriggerOperationError(Handle, FString("NOT_SIGNED_IN"));
	}
	return Handle;
}

FBeamOperationHandle UBeamLobbySubsystem::CPP_ProvisionGameServerForLobbyOperation(FUserSlot UserSlot, FOptionalBeamContentId NewGameType, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FBeamRealmUser SlotUser;
	if (UserSlots->GetUserDataAtSlot(UserSlot, SlotUser, this))
	{
		ProvisionGameServerForLobby(UserSlot, NewGameType, Handle);
	}
	else
	{
		RequestTracker->TriggerOperationError(Handle, FString("NOT_SIGNED_IN"));
	}
	return Handle;
}

// OPERATIONS Implementations

void UBeamLobbySubsystem::CreateOpenLobby(FUserSlot UserSlot, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags,
                                          FBeamOperationHandle Op)
{
	const auto Handler = FOnPostLobbiesFullResponse::CreateLambda([this, UserSlot, Op](FPostLobbiesFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UpdateLobbyPlayerInfo(UserSlot, Resp.SuccessData);
			ReplaceOrAddKnownLobbyData(Resp.SuccessData);
			RequestTracker->TriggerOperationSuccess(Op, Resp.SuccessData->LobbyId.Val);
			UE_LOG(LogBeamLobby, Verbose, TEXT("Created Open Lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s"), *Resp.SuccessData->LobbyId.Val, *Resp.SuccessData->Host.Val.AsString)
		}
	});


	FBeamRequestContext Ctx = RequestPostLobbies(UserSlot, Name, Desc, EBeamLobbyRestriction::BEAM_Open, MatchType, 0, MaxPlayers, LobbyData, PlayerTags, Op, Handler);
}

void UBeamLobbySubsystem::CreateClosedLobby(FUserSlot UserSlot, FString Name, FString Desc, FBeamContentId MatchType, int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags,
                                            FBeamOperationHandle Op)
{
	const auto Handler = FOnPostLobbiesFullResponse::CreateLambda([this, UserSlot, Op](FPostLobbiesFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UpdateLobbyPlayerInfo(UserSlot, Resp.SuccessData);
			ReplaceOrAddKnownLobbyData(Resp.SuccessData);
			RequestTracker->TriggerOperationSuccess(Op, Resp.SuccessData->LobbyId.Val);
			UE_LOG(LogBeamLobby, Verbose, TEXT("Created Closed Lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,PASSCODE=%s"),
			       *Resp.SuccessData->LobbyId.Val,
			       *Resp.SuccessData->Host.Val.AsString,
			       *Resp.SuccessData->Passcode.Val)
		}
	});

	FBeamRequestContext Ctx = RequestPostLobbies(UserSlot, Name, Desc, EBeamLobbyRestriction::BEAM_Closed, MatchType, PasscodeSize, MaxPlayers, LobbyData, PlayerTags, Op, Handler);
}

void UBeamLobbySubsystem::RefreshLobbyData(FUserSlot UserSlot, FGuid LobbyId, FBeamOperationHandle Op)
{
	const auto Handler = FOnGetLobbyFullResponse::CreateLambda([this, UserSlot, Op](FGetLobbyFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			// Add this lobby to the list of known lobbies
			ReplaceOrAddKnownLobbyData(Resp.SuccessData);

			// Whenever we get a lobby, we check if any of our local players are in one of these lobbies.  
			for (ULobbyPlayer* Val : Resp.SuccessData->Players.Val)
			{
				FBeamRealmUser Data;
				FUserSlot Slot;
				FString _;

				// If we are in this new lobby we just fetched... 
				if (UserSlots->GetUserDataWithGamerTag(Val->PlayerId.Val, Data, Slot, _))
				{
					// We check if the local lobby we "think" we are in is different than this new one that the server just told us we are in. If it is...
					if (LocalPlayerLobbyInfo[Slot]->LobbyId != FGuid(Resp.SuccessData->LobbyId.Val))
					{
						// Clear the slot
						ClearLobbyForSlot(Slot);

						// Update the LobbyPlayerInfo data with this lobby.
						UpdateLobbyPlayerInfo(Slot, Resp.SuccessData);
					}
				}
			}

			TArray<FString> PlayerIds;
			for (ULobbyPlayer* LobbyPlayer : Resp.SuccessData->Players.Val)
				PlayerIds.Add(LobbyPlayer->PlayerId.Val.AsString);

			UE_LOG(LogBeamLobby, Verbose, TEXT("Refreshed Lobby Data. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s,PASSCODE=%s,PLAYER_GAMERTAGS=[%s]"),
			       *Resp.SuccessData->LobbyId.Val,
			       *Resp.SuccessData->Host.Val.AsString,
			       !Resp.SuccessData->MatchType.IsSet ? TEXT("NoGameTypeInLobby") : *Resp.SuccessData->MatchType.Val->Id.Val.AsString,
			       *Resp.SuccessData->Passcode.Val,
			       *FString::Join(PlayerIds, TEXT(",")))
			RequestTracker->TriggerOperationSuccess(Op, Resp.SuccessData->LobbyId.Val);
		}
	});

	FBeamRequestContext Ctx = RequestGetLobby(UserSlot, LobbyId, Op, Handler);
}

void UBeamLobbySubsystem::RefreshLobbiesData(FUserSlot UserSlot, FBeamContentId MatchTypeFilter, int32 PageStart, int32 PageSize, FBeamOperationHandle Op)
{
	const auto Handler = FOnApiLobbyGetLobbiesFullResponse::CreateLambda([this, UserSlot, Op](FApiLobbyGetLobbiesFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			const auto OptionalLobbies = Resp.SuccessData->Results;
			bool bFoundLobbies;
			TArray<ULobby*> Lobbies = UOptionalArrayOfLobbyLibrary::GetOptionalValue(OptionalLobbies, {}, bFoundLobbies);
			for (ULobby* Lobby : Lobbies)
			{
				ReplaceOrAddKnownLobbyData(Lobby);

				TArray<FString> PlayerIds;
				for (ULobbyPlayer* LobbyPlayer : Lobby->Players.Val)
					PlayerIds.Add(LobbyPlayer->PlayerId.Val.AsString);

				UE_LOG(LogBeamLobby, Verbose, TEXT("Refreshed Lobby Data. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s,PASSCODE=%s,PLAYER_GAMERTAGS=[%s]"),
				       *Lobby->LobbyId.Val,
				       *Lobby->Host.Val.AsString,
				       *Lobby->MatchType.Val->Id.Val.AsString,
				       *Lobby->Passcode.Val,
				       *FString::Join(PlayerIds, TEXT(",")))
			}

			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		}
	});

	FBeamRequestContext Ctx = RequestGetLobbies(UserSlot, MatchTypeFilter, PageStart, PageSize, Op, Handler);
}

void UBeamLobbySubsystem::JoinLobby(FUserSlot UserSlot, FGuid LobbyId, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op)
{
	const auto Handler = FOnPutLobbyFullResponse::CreateLambda([this, UserSlot, Op](FPutLobbyFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UpdateLobbyPlayerInfo(UserSlot, Resp.SuccessData);
			ReplaceOrAddKnownLobbyData(Resp.SuccessData);
			RequestTracker->TriggerOperationSuccess(Op, Resp.SuccessData->LobbyId.Val);

			UE_LOG(LogBeamLobby, Verbose, TEXT("Joined Open Lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s"),
			       *Resp.SuccessData->LobbyId.Val,
			       *Resp.SuccessData->Host.Val.AsString,
			       !Resp.SuccessData->MatchType.IsSet ? TEXT("NoGameTypeInLobby") : *Resp.SuccessData->MatchType.Val->Id.Val.AsString)
		}
	});

	FBeamRequestContext Ctx = RequestJoin(UserSlot, LobbyId, PlayerTags, Op, Handler);
}

void UBeamLobbySubsystem::JoinLobbyByPasscode(FUserSlot UserSlot, FString Passcode, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op)
{
	const auto Handler = FOnPutPasscodeFullResponse::CreateLambda([this, UserSlot, Op](FPutPasscodeFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UpdateLobbyPlayerInfo(UserSlot, Resp.SuccessData);
			ReplaceOrAddKnownLobbyData(Resp.SuccessData);
			RequestTracker->TriggerOperationSuccess(Op, Resp.SuccessData->LobbyId.Val);

			UE_LOG(LogBeamLobby, Verbose, TEXT("Joined Closed Lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s, PASSCODE=%s"),
			       *Resp.SuccessData->LobbyId.Val,
			       *Resp.SuccessData->Host.Val.AsString,
			       !Resp.SuccessData->MatchType.IsSet ? TEXT("NoGameTypeInLobby") : *Resp.SuccessData->MatchType.Val->Id.Val.AsString,
			       *Resp.SuccessData->Passcode.Val)
		}
	});

	FBeamRequestContext Ctx = RequestJoinByPassword(UserSlot, Passcode, PlayerTags, Op, Handler);
}

void UBeamLobbySubsystem::LeaveLobby(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (!LocalPlayerLobbyInfo.Contains(UserSlot))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NOT_IN_LOBBY"));
		return;
	}

	const auto JoinedLobbyState = LocalPlayerLobbyInfo.FindChecked(UserSlot);
	const auto LobbyData = GetCurrentLobby(UserSlot);
	const auto Handler = FOnDeleteLobbyFullResponse::CreateLambda([this, Op, LobbyData](FDeleteLobbyFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			RequestTracker->TriggerOperationSuccess(Op, "");
			UE_LOG(LogBeamLobby, Verbose, TEXT("Left Lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s, PASSCODE=%s"),
			       *LobbyData->LobbyId.Val,
			       *LobbyData->Host.Val.AsString,
			       *LobbyData->MatchType.Val->Id.Val.AsString,
			       *LobbyData->Passcode.Val)
		}
	});

	// Get the player's GamerTag and leave the lobby they are in.
	FBeamRealmUser UserData;
	UserSlots->GetUserDataAtSlot(UserSlot, UserData, this);
	FBeamRequestContext Ctx = RequestRemoveFromLobby(UserSlot, JoinedLobbyState->LobbyId, UserData.GamerTag, Op, Handler);
}

void UBeamLobbySubsystem::KickPlayer(FUserSlot UserSlot, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	if (!LocalPlayerLobbyInfo.Contains(UserSlot))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NOT_IN_LOBBY"));
		return;
	}

	const auto JoinedLobbyState = *LocalPlayerLobbyInfo.Find(UserSlot);
	const auto LobbyData = GetCurrentLobby(UserSlot);
	if (!JoinedLobbyState->bIsLobbyOwner)
	{
		UE_LOG(LogBeamLobby, Verbose, TEXT("Tried to kick player without being the host. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s, PASSCODE=%s"),
		       *LobbyData->LobbyId.Val,
		       *LobbyData->Host.Val.AsString,
		       *LobbyData->MatchType.Val->Id.Val.AsString,
		       *LobbyData->Passcode.Val)
		RequestTracker->TriggerOperationError(Op, TEXT("NOT_LOBBY_HOST"));
		return;
	}

	const auto Handler = FOnDeleteLobbyFullResponse::CreateLambda([this, LobbyData, Op, Player](FDeleteLobbyFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UE_LOG(LogBeamLobby, Verbose, TEXT("Successfully kicked player from lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s,GAMERTAG=%s"),
			       *LobbyData->LobbyId.Val,
			       *LobbyData->Host.Val.AsString,
			       *LobbyData->MatchType.Val->Id.Val.AsString,
			       *Player.AsString)
			RequestTracker->TriggerOperationSuccess(Op, "");
		}
	});

	// Get the player's GamerTag and leave the lobby they are in.	
	FBeamRequestContext Ctx = RequestRemoveFromLobby(UserSlot, JoinedLobbyState->LobbyId, Player, Op, Handler);
}

void UBeamLobbySubsystem::CommitLobbyUpdate(const FUserSlot& Slot, FBeamOperationHandle Op)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState))
	{
		RequestTracker->TriggerOperationError(Op, FString("NOT_IN_LOBBY"));
		return;
	}

	if (!GuardUpdateCommandBegun(Slot))
	{
		RequestTracker->TriggerOperationError(Op, FString("NO_LOBBY_UPDATE_PREPARED"));
		return;
	}

	const auto UpdateCmd = UpdateCommands[Slot];
	const auto LobbyId = UpdateCmd->LobbyId;

	// If we don't actually have any update, we just trigger the success without making any requests.
	if (!UpdateCmd->HasGlobalDataUpdate())
	{
		RequestTracker->TriggerOperationSuccess(Op, LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower));
		return;
	}

	// If we do have an update... we make the request to update it.
	const auto NewName = UpdateCmd->NewLobbyName;
	const auto NewDesc = UpdateCmd->NewLobbyDescription;
	const auto NewRestriction = UpdateCmd->NewRestriction;
	const auto NewGameType = UpdateCmd->NewGameType;
	const auto NewHost = UpdateCmd->NewHost;
	const auto NewMaxPlayers = UpdateCmd->NewMaxPlayers;
	const auto GlobalDataUpdates = UpdateCmd->GlobalDataUpdates;
	const auto GlobalDataDeletes = UpdateCmd->GlobalDataDeletes;

	const auto Handler = FOnApiLobbyPutMetadataByIdFullResponse::CreateLambda([this, Slot, Op, LobbyId, GlobalDataUpdates, GlobalDataDeletes](FApiLobbyPutMetadataByIdFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		ReplaceOrAddKnownLobbyData(Resp.SuccessData);
		UpdateCommands.Remove(Slot);

		auto AddedOrUpdatedGlobalDataLog = FString("");
		auto RemovedGlobalDataLog = FString("");

		if (GlobalDataUpdates.IsSet)
		{
			for (auto Val : GlobalDataUpdates.Val)
				AddedOrUpdatedGlobalDataLog += FString::Printf(TEXT("(%s,%s), "), *Val.Key, *Val.Value);
		}

		if (GlobalDataDeletes.IsSet)
		{
			for (auto Val : GlobalDataDeletes.Val)
				RemovedGlobalDataLog += FString::Printf(TEXT("%s, "), *Val);
		}

		RequestTracker->TriggerOperationSuccess(Op, LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower));

		UE_LOG(LogBeamLobby, Verbose, TEXT("Successfully updated data for the lobby. LOBBY_ID=%s,HOST_PLAYER_GAMERTAG=%s,GAME_TYPE=%s,GLOBAL_DATA_ADDED=%s,GLOBAL_DATA_REMOVED=%s"),
		       *Resp.SuccessData->LobbyId.Val,
		       *Resp.SuccessData->Host.Val.AsString,
		       !Resp.SuccessData->MatchType.IsSet ? TEXT("NoGameTypeInLobby") : *Resp.SuccessData->MatchType.Val->Id.Val.AsString,
		       *AddedOrUpdatedGlobalDataLog,
		       *RemovedGlobalDataLog)
	});
	auto _ = RequestUpdateLobbyMetadata(Slot, LobbyId, NewName, NewDesc, NewRestriction, NewGameType, NewHost, NewMaxPlayers, GlobalDataUpdates, GlobalDataDeletes, Op, Handler);
}

void UBeamLobbySubsystem::UpdatePlayerTags(const FUserSlot& Slot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, bool bShouldReplaceRepeatedTags, FBeamOperationHandle Op)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState))
	{
		RequestTracker->TriggerOperationError(Op, FString("NOT_IN_LOBBY"));
		return;
	}

	// If the target player is not in the lobby, we fail the operation.
	const auto Lobby = GetCurrentLobby(Slot);
	if (!Lobby->Players.Val.ContainsByPredicate([TargetPlayer](const ULobbyPlayer* P) { return P->PlayerId.Val == TargetPlayer; }))
	{
		RequestTracker->TriggerOperationError(Op, FString("TARGET_PLAYER_NOT_IN_LOBBY"));
		return;
	}

	// If we are not the owner, we can only change our own tags.
	if (!LobbyState->bIsLobbyOwner)
	{
		FBeamRealmUser RequestingUser;
		UserSlots->GetUserDataAtSlot(Slot, RequestingUser, this);
		if (RequestingUser.GamerTag != TargetPlayer)
		{
			RequestTracker->TriggerOperationError(Op, FString("CANNOT_MODIFY_OTHER_PLAYER_TAGS_IF_NOT_HOST"));
			return;
		}
	}

	// Make the request.
	const auto LobbyId = LobbyState->LobbyId;
	const auto Handler = FOnPutTagsFullResponse::CreateLambda([this, Slot, Op, LobbyId, TargetPlayer, Tags](FPutTagsFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		ReplaceOrAddKnownLobbyData(Resp.SuccessData);
		auto AddedOrUpdatedTags = FString("");
		for (auto Val : Tags)
			AddedOrUpdatedTags += FString::Printf(TEXT("(%s,%s), "), *Val.Name.Val, *Val.Value.Val);
		RequestTracker->TriggerOperationSuccess(Op, LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower));

		UE_LOG(LogBeamLobby, Verbose, TEXT("Successfully updated data for the lobby. REQUESTING_SLOT=%s, LOBBY_ID=%s,MODIFIED_PLAYER_GAMERTAG=%s,PLAYER_TAGS=%s"),
		       *Slot.Name,
		       *Resp.SuccessData->LobbyId.Val,
		       *TargetPlayer.AsString,
		       *AddedOrUpdatedTags)
	});

	auto _ = RequestUpdatePlayerTag(Slot, LobbyId, TargetPlayer, Tags, bShouldReplaceRepeatedTags, Op, Handler);
}

void UBeamLobbySubsystem::DeletePlayerTags(const FUserSlot& Slot, FBeamGamerTag TargetPlayer, TArray<FBeamTag> Tags, FBeamOperationHandle Op)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState))
	{
		RequestTracker->TriggerOperationError(Op, FString("NOT_IN_LOBBY"));
		return;
	}

	// If the target player is not in the lobby, we fail the operation.
	const auto Lobby = GetCurrentLobby(Slot);
	const auto LobbyId = LobbyState->LobbyId;
	if (!Lobby->Players.Val.ContainsByPredicate([TargetPlayer](const ULobbyPlayer* P) { return P->PlayerId.Val == TargetPlayer; }))
	{
		RequestTracker->TriggerOperationError(Op, FString("TARGET_PLAYER_NOT_IN_LOBBY"));
		return;
	}

	// If we are not the owner, we can only change our own tags.
	if (!LobbyState->bIsLobbyOwner)
	{
		FBeamRealmUser RequestingUser;
		UserSlots->GetUserDataAtSlot(Slot, RequestingUser, this);
		if (RequestingUser.GamerTag != TargetPlayer)
		{
			RequestTracker->TriggerOperationError(Op, FString("CANNOT_MODIFY_OTHER_PLAYER_TAGS_IF_NOT_HOST"));
			return;
		}
	}

	// Make sure no accidental unset tag is being given
	TArray<FBeamTag> TagsToRemove;
	for (FBeamTag Tag : Tags)
	{
		if (Tag.Name.IsSet)
		{
			TagsToRemove.Add(Tag);
		}
		else
		{
			UE_LOG(LogBeamLobby, Verbose, TEXT("Skipping tag with no name set when trying to update the tags for this player. REQUESTING_SLOT=%s, LOBBY_ID=%s,MODIFIED_PLAYER_GAMERTAG=%s"),
			       *Slot.Name,
			       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower),
			       *TargetPlayer.AsString)
		}
	}

	// Make the request.
	const auto Handler = FOnDeleteTagsFullResponse::CreateLambda([this, Slot, Op, LobbyId, TargetPlayer, TagsToRemove](FDeleteTagsFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		ReplaceOrAddKnownLobbyData(Resp.SuccessData);
		auto DeletedTags = FString("");
		for (auto Val : TagsToRemove)
			DeletedTags += FString::Printf(TEXT("(%s,%s), "), *Val.Name.Val, *Val.Value.Val);
		RequestTracker->TriggerOperationSuccess(Op, LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower));

		UE_LOG(LogBeamLobby, Verbose, TEXT("Successfully updated data for the lobby. REQUESTING_SLOT=%s, LOBBY_ID=%s,MODIFIED_PLAYER_GAMERTAG=%s,PLAYER_TAGS=%s"),
		       *Slot.Name,
		       *Resp.SuccessData->LobbyId.Val,
		       *TargetPlayer.AsString,
		       *DeletedTags)
	});

	auto _ = RequestDeletePlayerTags(Slot, LobbyId, TargetPlayer, TagsToRemove, Op, Handler);
}

void UBeamLobbySubsystem::ProvisionGameServerForLobby(const FUserSlot& Slot, FOptionalBeamContentId NewGameContent, FBeamOperationHandle Op)
{
	UBeamLobbyState* LobbyState;
	if (!GuardSlotIsInLobby(Slot, LobbyState))
	{
		RequestTracker->TriggerOperationError(Op, FString("NOT_IN_LOBBY"));
		return;
	}

	// If we are not the owner, we can only change our own tags.
	if (!GuardIsLobbyOwner(Slot, LobbyState))
	{
		RequestTracker->TriggerOperationError(Op, FString("NOT_LOBBY_OWNER"));
		return;
	}

	auto Handler = FOnApiLobbyPostServerByIdFullResponse::CreateLambda([this, Slot, Op, LobbyState](FApiLobbyPostServerByIdFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		UE_LOG(LogBeamLobby, Verbose,
		       TEXT("Successfully provisioned a server. Now, on LobbyUpdated event, code should be extracting connection parameters from ULobby::Data. REQUESTING_SLOT=%s, LOBBY_ID=%s"),
		       *Slot.Name,
		       *LobbyState->LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower))
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
	});

	auto _ = RequestPostServer(Slot, LobbyState->LobbyId, NewGameContent, Op, Handler);
}

// REQUEST HELPERS

FBeamRequestContext UBeamLobbySubsystem::RequestJoin(const FUserSlot& UserSlot, FGuid LobbyId, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op, FOnPutLobbyFullResponse Handler) const
{
	const auto Req = UPutLobbyRequest::Make(
		LobbyId,
		FOptionalString(),
		PlayerTags.Num() ? FOptionalArrayOfBeamTag(PlayerTags) : FOptionalArrayOfBeamTag(),
		GetTransientPackage(),
		{});

	FBeamRequestContext Ctx;
	LobbyApi->CPP_PutLobby(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestJoinByPassword(const FUserSlot& UserSlot, FString Passcode, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op,
                                                               FOnPutPasscodeFullResponse Handler) const
{
	const auto Req = UPutPasscodeRequest::Make(
		FOptionalString(Passcode),
		PlayerTags.Num() ? FOptionalArrayOfBeamTag(PlayerTags) : FOptionalArrayOfBeamTag(),
		GetTransientPackage(),
		{});

	FBeamRequestContext Ctx;
	LobbyApi->CPP_PutPasscode(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestGetLobby(const FUserSlot& UserSlot, FGuid LobbyId, FBeamOperationHandle Op, FOnGetLobbyFullResponse Handler) const
{
	const auto Req = UGetLobbyRequest::Make(LobbyId, GetTransientPackage(), {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_GetLobby(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestGetLobbies(const FUserSlot& UserSlot, FBeamContentId MatchTypeFilter, int32 PageStart, int32 PageSize, FBeamOperationHandle Op,
                                                           FOnApiLobbyGetLobbiesFullResponse Handler) const
{
	const auto Req = UApiLobbyGetLobbiesRequest::Make(
		PageStart < 0 ? FOptionalInt32() : FOptionalInt32(PageStart),
		PageSize < 0 ? FOptionalInt32() : FOptionalInt32(PageSize),
		MatchTypeFilter.AsString.IsEmpty() ? FOptionalBeamContentId() : FOptionalBeamContentId(MatchTypeFilter),
		GetTransientPackage(),
		{});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_GetLobbies(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestPostLobbies(const FUserSlot& UserSlot, FString LobbyName, FString LobbyDescription, EBeamLobbyRestriction Restriction, FBeamContentId MatchType,
                                                            int32 PasscodeLength, int32 MaxPlayers, TMap<FString, FString> LobbyData, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op,
                                                            FOnPostLobbiesFullResponse Handler) const
{
	// Build the request
	auto Req = UPostLobbiesRequest::Make(FOptionalString{LobbyName},
	                                     FOptionalString(LobbyDescription),
	                                     FOptionalLobbyRestriction(Restriction),
	                                     !MatchType.AsString.IsEmpty() ? FOptionalBeamContentId(MatchType) : FOptionalBeamContentId(),
	                                     Restriction == EBeamLobbyRestriction::BEAM_Closed ? FOptionalInt32(PasscodeLength) : FOptionalInt32(),
	                                     MaxPlayers ? FOptionalInt32(MaxPlayers) : FOptionalInt32(),
	                                     PlayerTags.Num() ? FOptionalArrayOfBeamTag(PlayerTags) : FOptionalArrayOfBeamTag(),
	                                     LobbyData.Num() ? FOptionalMapOfString{LobbyData} : FOptionalMapOfString(),
	                                     GetTransientPackage(),
	                                     {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_PostLobbies(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestRemoveFromLobby(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag GamerTag, FBeamOperationHandle Op, FOnDeleteLobbyFullResponse Handler) const
{
	const auto Req = UDeleteLobbyRequest::Make(LobbyId, FOptionalBeamGamerTag(GamerTag), GetTransientPackage(), {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_DeleteLobby(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestUpdateLobbyMetadata(const FUserSlot& UserSlot, FGuid LobbyId, FOptionalString LobbyName, FOptionalString LobbyDescription,
                                                                    FOptionalLobbyRestriction Restriction,
                                                                    FOptionalBeamContentId MatchType, FOptionalBeamGamerTag NewHost, FOptionalInt32 MaxPlayers,
                                                                    FOptionalMapOfString GlobalDataUpdates, FOptionalArrayOfString GlobalDataDeletes, FBeamOperationHandle Op,
                                                                    FOnApiLobbyPutMetadataByIdFullResponse Handler) const
{
	FOptionalUpdateData OptionalUpdateData = FOptionalUpdateData(NewObject<UUpdateData>());
	OptionalUpdateData.Val->Updates = GlobalDataUpdates;
	OptionalUpdateData.Val->Deletes = GlobalDataDeletes;

	const auto Req = UApiLobbyPutMetadataByIdRequest::Make(LobbyId,
	                                                       LobbyName,
	                                                       LobbyDescription,
	                                                       Restriction,
	                                                       MatchType,
	                                                       MaxPlayers,
	                                                       NewHost.IsSet ? FOptionalString(NewHost.Val.AsString) : FOptionalString(),
	                                                       OptionalUpdateData,
	                                                       GetTransientPackage(), {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_PutMetadata(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestUpdatePlayerTag(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag PlayerId, TArray<FBeamTag> PlayerTags, bool bShouldReplace,
                                                                FBeamOperationHandle Op, FOnPutTagsFullResponse Handler) const
{
	const auto Req = UPutTagsRequest::Make(LobbyId,
	                                       FOptionalBeamGamerTag(PlayerId),
	                                       FOptionalBool(bShouldReplace),
	                                       PlayerTags.Num() > 0 ? FOptionalArrayOfBeamTag(PlayerTags) : FOptionalArrayOfBeamTag(),
	                                       GetTransientPackage(), {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_PutTags(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestDeletePlayerTags(const FUserSlot& UserSlot, FGuid LobbyId, FBeamGamerTag PlayerId, TArray<FBeamTag> PlayerTags, FBeamOperationHandle Op,
                                                                 FOnDeleteTagsFullResponse Handler) const
{
	TArray<FString> TagsToRemove;
	for (FBeamTag PlayerTag : PlayerTags)
	{
		TagsToRemove.Add(PlayerTag.Name.Val);
	}
	const auto Req = UDeleteTagsRequest::Make(LobbyId,
	                                          FOptionalBeamGamerTag(PlayerId),
	                                          FOptionalArrayOfString(TagsToRemove),
	                                          GetTransientPackage(), {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_DeleteTags(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamLobbySubsystem::RequestPostServer(const FUserSlot& UserSlot, FGuid LobbyId, FOptionalBeamContentId SelectedMatchType, FBeamOperationHandle Op,
                                                           FOnApiLobbyPostServerByIdFullResponse Handler) const
{
	const auto Req = UApiLobbyPostServerByIdRequest::Make(LobbyId,
	                                                      SelectedMatchType,
	                                                      GetTransientPackage(),
	                                                      {});

	// Make the request
	FBeamRequestContext Ctx;
	LobbyApi->CPP_PostServer(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

// NOTIFICATION HANDLERS

void UBeamLobbySubsystem::OnLobbyUpdatedHandler(FLobbyUpdateNotificationMessage Msg, FUserSlot Slot)
{
	if (Msg.Type == EBeamLobbyEvent::BEAM_LobbyDisbanded)
	{
		if (UBeamLobbyState** Info = LocalPlayerLobbyInfo.Find(Slot))
		{
			UBeamLobbyState* Lobby = *Info;
			const auto LobbyId = Msg.LobbyId;

			ULobby* LobbyData;
			if (TryGetLobbyById(LobbyId, LobbyData) && Lobby->LobbyId == LobbyId)
			{
				Lobby->OnLobbyDisbandedCode.Broadcast(Slot, LobbyData, Msg);
				Lobby->OnLobbyDisbanded.Broadcast(Slot, LobbyData, Msg);
				ClearLobbyForSlot(Slot);
				UE_LOG(LogBeamLobby, Verbose, TEXT("Cleared lobby data due to lobby being disbanded. LOBBY_ID=%s, USER_SLOT=%s"), *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
			}
			else
			{
				UE_LOG(LogBeamLobby, Verbose, TEXT("Local Lobby was already cleaned up when we got this notification, so we're not doing anything. LOBBY_ID=%s, USER_SLOT=%s"),
				       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
			}
		}
	}

	if (Msg.Type == EBeamLobbyEvent::BEAM_DataChanged || Msg.Type == EBeamLobbyEvent::BEAM_PlayerJoined || Msg.Type == EBeamLobbyEvent::BEAM_LobbyCreated)
	{
		if (UBeamLobbyState** Info = LocalPlayerLobbyInfo.Find(Slot))
		{
			const auto Lobby = *Info;
			auto LobbyId = Msg.LobbyId;

			// First we check if this local player was in the lobby.
			const auto bWasNotInLobby = Lobby->LobbyId == FGuid();

			// Refresh the lobby's data and notify the user that the lobby data has changed. 
			CPP_RefreshLobbyDataOperation(Slot, FBeamOperationEventHandlerCode::CreateLambda([this, bWasNotInLobby, Slot, LobbyId, Lobby, Msg](FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					ULobby* LobbyData;
					if (TryGetLobbyById(LobbyId, LobbyData))
					{
						// If this local player was the one who joined the lobby (was not in any lobby, but is in the refreshed lobby)
						if (bWasNotInLobby && Lobby->LobbyId == Msg.LobbyId && Msg.Type == EBeamLobbyEvent::BEAM_PlayerJoined)
						{
							Lobby->OnLobbyJoinedCode.Broadcast(Slot, LobbyData, Msg);
							Lobby->OnLobbyJoined.Broadcast(Slot, LobbyData, Msg);
							UE_LOG(LogBeamLobby, Verbose, TEXT("Lobby joined due to %s. LOBBY_ID=%s, USER_SLOT=%s"), *StaticEnum<EBeamLobbyEvent>()->GetNameStringByValue(static_cast<int64>(Msg.Type)),
							       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
						}
						else
						{
							Lobby->OnLobbyUpdatedCode.Broadcast(Slot, LobbyData, Msg);
							Lobby->OnLobbyUpdated.Broadcast(Slot, LobbyData, Msg);
							UE_LOG(LogBeamLobby, Verbose, TEXT("Lobby data refreshed due to %s.LOBBY_ID=%s, USER_SLOT=%s"),
							       *StaticEnum<EBeamLobbyEvent>()->GetNameStringByValue(static_cast<int64>(Msg.Type)),
							       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
						}
					}
					else
					{
						UE_LOG(LogBeamLobby, Error, TEXT("You should not be seeing this. LOBBY_ID=%s, USER_SLOT=%s"), *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
					}
				}
			}), LobbyId);
		}
	}


	if (Msg.Type == EBeamLobbyEvent::BEAM_PlayerKicked)
	{
		if (UBeamLobbyState** Info = LocalPlayerLobbyInfo.Find(Slot))
		{
			auto Lobby = *Info;
			const auto LobbyId = Msg.LobbyId;

			// Refresh the lobby's data and notify the user that the lobby data has changed. 
			CPP_RefreshLobbyDataOperation(Slot, FBeamOperationEventHandlerCode::CreateLambda([this, Slot, LobbyId, Lobby, Msg](FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					ULobby* LobbyData;
					if (TryGetLobbyById(LobbyId, LobbyData))
					{
						// If you're no longer in the lobby, it means you were the kicked player, so we trigger the kicked callbacks.
						if (!LobbyData->Players.Val.FindByPredicate([Lobby](ULobbyPlayer*& P) { return P->PlayerId.Val.AsLong == Lobby->OwnerGamerTag; }))
						{
							Lobby->OnKickedFromLobbyCode.Broadcast(Slot, LobbyData, Msg);
							Lobby->OnKickedFromLobby.Broadcast(Slot, LobbyData, Msg);
							ClearLobbyForSlot(Slot);
							UE_LOG(LogBeamLobby, Verbose, TEXT("Lobby cleared due to the local player player being kicked from the lobby. LOBBY_ID=%s, USER_SLOT=%s"),
							       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
						}
						// If you're still in the lobby, we just trigger the updated callbacks.
						else
						{
							Lobby->OnLobbyUpdatedCode.Broadcast(Slot, LobbyData, Msg);
							Lobby->OnLobbyUpdated.Broadcast(Slot, LobbyData, Msg);
							UE_LOG(LogBeamLobby, Verbose, TEXT("Lobby data refreshed due to a player being kicked the lobby remotely. LOBBY_ID=%s, USER_SLOT=%s"),
							       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
						}
					}
					else
					{
						UE_LOG(LogBeamLobby, Error, TEXT("You should not be seeing this. LOBBY_ID=%s, USER_SLOT=%s"), *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
					}
				}
			}), LobbyId);
		}
	}

	if (Msg.Type == EBeamLobbyEvent::BEAM_PlayerLeft)
	{
		if (UBeamLobbyState** Info = LocalPlayerLobbyInfo.Find(Slot))
		{
			auto Lobby = *Info;
			const auto LobbyId = Msg.LobbyId;

			// Refresh the lobby's data and notify the user that the lobby data has changed. 
			CPP_RefreshLobbyDataOperation(Slot, FBeamOperationEventHandlerCode::CreateLambda([this, Slot, LobbyId, Lobby, Msg](FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					ULobby* LobbyData;
					if (TryGetLobbyById(LobbyId, LobbyData))
					{
						// If you're no longer in the lobby, it means you were the player that left, so we trigger the left lobby callbacks.
						if (!LobbyData->Players.Val.FindByPredicate([Lobby](ULobbyPlayer*& P) { return P->PlayerId.Val.AsLong == Lobby->OwnerGamerTag; }))
						{
							Lobby->OnLeftLobbyCode.Broadcast(Slot, LobbyData, Msg);
							Lobby->OnLeftLobby.Broadcast(Slot, LobbyData, Msg);
							ClearLobbyForSlot(Slot);
							UE_LOG(LogBeamLobby, Verbose, TEXT("Lobby cleared due to the local player leaving the lobby manually. LOBBY_ID=%s, USER_SLOT=%s"),
							       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
						}
						// Otherwise, you're still in the lobby and we trigger the Update callbacks.
						else
						{
							Lobby->OnLobbyUpdatedCode.Broadcast(Slot, LobbyData, Msg);
							Lobby->OnLobbyUpdated.Broadcast(Slot, LobbyData, Msg);
							UE_LOG(LogBeamLobby, Verbose, TEXT("Lobby data refreshed due to a player leaving the lobby remotely. LOBBY_ID=%s, USER_SLOT=%s"),
							       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower), *Slot.Name);
						}
					}
					else
					{
						UE_LOG(LogBeamLobby, Error, TEXT("You should not be seeing this. This lobby should be here if the operation succeeded. LOBBY_ID=%s, USER_SLOT=%s"),
						       *LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower),
						       *Slot.Name);
					}
				}
				else
				{
					UE_LOG(LogBeamLobby, Error, TEXT("Failed to refresh the lobby data. %s"), *Evt.EventCode);
				}
			}), LobbyId);
		}
	}
}

// HELPER FUNCTIONS
void UBeamLobbySubsystem::InitializeLobbyInfoForSlot(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser)
{
	const auto LobbyUpdateHandler = FOnLobbyUpdateNotificationCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, OnLobbyUpdatedHandler), UserSlot);
	const auto Handle = LobbyNotification->CPP_SubscribeToLobbyUpdate(UserSlot, Runtime->DefaultNotificationChannel, LobbyUpdateHandler, this);

	LocalPlayerLobbyInfo.Add(UserSlot, NewObject<UBeamLobbyState>());
	LocalPlayerLobbyInfo[UserSlot]->LobbyId = FGuid();
	LocalPlayerLobbyInfo[UserSlot]->bIsLobbyOwner = false;
	LocalPlayerLobbyInfo[UserSlot]->OwnerUserSlot = UserSlot;
	LocalPlayerLobbyInfo[UserSlot]->OwnerGamerTag = BeamRealmUser.GamerTag;
	LocalPlayerLobbyInfo[UserSlot]->NotificationSubscriptionHandle = Handle;
}

void UBeamLobbySubsystem::UpdateLobbyPlayerInfo(const FUserSlot Slot, const ULobby* LobbyData)
{
	UBeamLobbyState* LobbyInfo = LocalPlayerLobbyInfo.FindRef(Slot);
	LobbyInfo->LobbyId = FGuid(LobbyData->LobbyId.Val);
	LobbyInfo->bIsLobbyOwner = LobbyData->Host.Val == LobbyInfo->OwnerGamerTag;
}

void UBeamLobbySubsystem::ReplaceOrAddKnownLobbyData(ULobby* LobbyData)
{
	if (const auto ExistingLobbyIdx = KnownLobbies.IndexOfByPredicate([LobbyData](const ULobby* Lob) { return Lob->LobbyId.Val.Equals(LobbyData->LobbyId.Val); }); ExistingLobbyIdx != INDEX_NONE)
		KnownLobbies[ExistingLobbyIdx] = LobbyData;
	else
		KnownLobbies.Add(LobbyData);
}

void UBeamLobbySubsystem::ClearLobbyForSlot(FUserSlot Slot)
{
	const auto Lobby = LocalPlayerLobbyInfo[Slot];
	Lobby->LobbyId = FGuid();
	Lobby->bIsLobbyOwner = false;

	Lobby->OnLobbyUpdatedCode.Clear();
	Lobby->OnLobbyUpdated.Clear();
}

bool UBeamLobbySubsystem::GuardSlotIsInLobby(const FUserSlot& Slot, UBeamLobbyState*& LobbyState)
{
	if (!TryGetCurrentLobbyState(Slot, LobbyState))
	{
		ensureAlwaysMsgf(false, TEXT("User at this slot is not in a lobby (locally). USER_SLOT=%s"), *Slot.Name);
		return false;
	}
	return true;
}

bool UBeamLobbySubsystem::GuardIsLobbyOwner(const FUserSlot& Slot, UBeamLobbyState* LobbyState)
{
	if (!LobbyState->bIsLobbyOwner)
	{
		ensureAlwaysMsgf(false, TEXT("The User at this slot is not lobby owner so it can't change its name. USER_SLOT=%s"), *Slot.Name);
		return false;
	}
	return true;
}

bool UBeamLobbySubsystem::GuardUpdateCommandBegun(const FUserSlot& Slot)
{
	if (!UpdateCommands.Contains(Slot))
	{
		ensureAlwaysMsgf(false, TEXT("Please call TryBeginUpdateLobbyData before using the various PrepareUpdate_____ functions. USER_SLOT=%s"), *Slot.Name);
		return false;
	}
	return true;
}
