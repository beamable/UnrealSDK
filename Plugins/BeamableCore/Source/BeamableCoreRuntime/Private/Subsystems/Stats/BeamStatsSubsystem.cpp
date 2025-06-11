// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================


#include "Subsystems/Stats/BeamStatsSubsystem.h"

void UBeamStatUpdateCommand::Init(UBeamStatsSubsystem* Subsystem, FUserSlot Slot, FBeamStatsType Type, TMap<FString, FString> StartingStats)
{
	StatsSubsystem = Subsystem;
	UserSlot = Slot;
	StatType = Type;

	StatNames.Reserve(StartingStats.Num());
	StatValues.Reserve(StartingStats.Num());
	for (auto StartingStat : StartingStats)
	{
		StatNames.Add(StartingStat.Key);
		StatValues.Add(StartingStat.Value);
	}
}

void UBeamStatUpdateCommand::AddStat(FString Key, FString Value)
{
	StatsSubsystem->AddStatToUpdateCommand(UserSlot, Key, Value);
}

void UBeamStatUpdateCommand::AddStats(TArray<FString> Key, TArray<FString> Value)
{
	ensureAlwaysMsgf(Key.Num() == Value.Num(), TEXT("Key and Value arrays must be parallel. KEY_NUM=%d, VALUE_NUM=%d"), Key.Num(), Value.Num());

	for (int i = 0; i < Key.Num(); ++i) StatsSubsystem->AddStatToUpdateCommand(UserSlot, Key[i], Value[i]);
}

void UBeamStatUpdateCommand::AddStatsMap(TMap<FString, FString> Stats)
{
	for (const auto& Stat : Stats) StatsSubsystem->AddStatToUpdateCommand(UserSlot, Stat.Key, Stat.Value);
}

void UBeamStatUpdateCommand::RemoveStat(FString Key)
{
	StatsSubsystem->RemoveStatFromUpdateCommand(UserSlot, Key);
}

void UBeamStatUpdateCommand::Discard()
{
	StatsSubsystem->ResetUpdateCommand(UserSlot);
}

TMap<FString, FString> UBeamStatUpdateCommand::AsMap()
{
	TMap<FString, FString> Map;
	check(StatNames.Num() == StatValues.Num())

	for (int i = 0; i < StatNames.Num(); ++i)
	{
		const FString Key = StatNames[i];
		const FString Val = StatValues[i];

		Map.Add(Key, Val);
	}

	return Map;
}


/* * STATS SUBSYSTEM - Initialization * */

void UBeamStatsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UserSlots = Runtime->UserSlotSystem;
	RequestTracker = Runtime->RequestTrackerSystem;
	StatsApi = GEngine->GetEngineSubsystem<UBeamStatsApi>();
}

void UBeamStatsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBeamStatsSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	const FBeamGamerTag UserGamerTag = BeamRealmUser.GamerTag;

	const UEnum* DomainEnum = StaticEnum<EBeamStatsDomain>();
	const UEnum* VisibilityEnum = StaticEnum<EBeamStatsVisibility>();
	for (int i = 0; i < DomainEnum->NumEnums(); ++i)
	{
		EBeamStatsDomain Domain = static_cast<EBeamStatsDomain>(DomainEnum->GetValueByIndex(i));
		for (int i2 = 0; i2 < VisibilityEnum->NumEnums(); ++i2)
		{
			EBeamStatsVisibility Visibility = static_cast<EBeamStatsVisibility>(VisibilityEnum->GetValueByIndex(i2));
			FBeamStatsType Type = UBeamStatsTypeLibrary::MakeStatsType(Domain, Visibility, UserGamerTag);

			UBeamStatsState* UserStatsState = NewObject<UBeamStatsState>();
			UserStatsState->OwnerType = Type;
			PlayerStatCache.Add(Type, UserStatsState);
		}
	}

	FBeamStatsType ClientPublicStats = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, UserGamerTag);
	ResultOp = RefreshStatsOperation(UserSlot, ClientPublicStats, {});
}

void UBeamStatsSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	// Let's just stop keeping a cache for each possible user key when they log out.
	const FBeamGamerTag UserGamerTag = BeamRealmUser.GamerTag;
	const UEnum* DomainEnum = StaticEnum<EBeamStatsDomain>();
	const UEnum* VisibilityEnum = StaticEnum<EBeamStatsVisibility>();
	for (int i = 0; i < DomainEnum->NumEnums(); ++i)
	{
		const auto Domain = static_cast<EBeamStatsDomain>(DomainEnum->GetValueByIndex(i));
		for (int i2 = 0; i2 < VisibilityEnum->NumEnums(); ++i2)
		{
			const auto Visibility = static_cast<EBeamStatsVisibility>(VisibilityEnum->GetValueByIndex(i2));
			auto Type = UBeamStatsTypeLibrary::MakeStatsType(Domain, Visibility, UserGamerTag);
			PlayerStatCache.Remove(Type);
		}
	}

	return Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

/* * STATS SUBSYSTEM - Update Command * */

bool UBeamStatsSubsystem::TryCreateUpdateCommand(FUserSlot Slot, const TMap<FString, FString>& Stats, UBeamStatUpdateCommand*& Command)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		Command = nullptr;
		return false;
	}

	// If we already have
	if (UpdateCommands.Contains(Slot))
	{
		UE_LOG(LogBeamStats, Warning, TEXT("Trying to start a new update command while one is building."))
		Command = nullptr;
		return false;
	}

	// Get the stat key for this user
	auto Stat = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);

	// Create a new update command buffer from it.
	Command = NewObject<UBeamStatUpdateCommand>(GetTransientPackage());
	Command->Init(this, Slot, Stat, Stats);

	UpdateCommands.Add(Slot, Command);
	return true;
}

void UBeamStatsSubsystem::AddStatToUpdateCommand(FUserSlot Slot, FString Key, FString Value)
{
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(Slot);
	const int32 Idx = CommandBuffer->StatNames.AddUnique(Key);

	if (const bool bWasNewStat = Idx == CommandBuffer->StatValues.Num())
		CommandBuffer->StatValues.AddUninitialized();

	CommandBuffer->StatValues[Idx] = Value;
}

void UBeamStatsSubsystem::RemoveStatFromUpdateCommand(FUserSlot Slot, FString Key)
{
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(Slot);
	const int32 Idx = CommandBuffer->StatNames.Find(Key);
	CommandBuffer->StatNames.RemoveAt(Idx);
	CommandBuffer->StatValues.RemoveAt(Idx);
}

void UBeamStatsSubsystem::ResetUpdateCommand(FUserSlot Slot)
{
	UpdateCommands.Remove(Slot);
}

/* * STATS SUBSYSTEM - Read Local State * */


bool UBeamStatsSubsystem::TryGetAllStats(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, TArray<FString>& Keys, TArray<FString>& Values)
{
	FBeamRealmUser OutRealmUser;
	if (UserSlots->GetUserDataAtSlot(Slot, OutRealmUser, this))
	{
		const auto StatType = UBeamStatsTypeLibrary::MakeStatsType(StatDomain, StatVisibility, OutRealmUser.GamerTag);
		return _TryGetAllStats(StatType, Keys, Values);
	}
	return false;
}

bool UBeamStatsSubsystem::TryGetAllStatsByGamerTag(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, FBeamGamerTag StatOwner, TArray<FString>& Keys, TArray<FString>& Values)
{
	const auto StatType = UBeamStatsTypeLibrary::MakeStatsType(StatDomain, StatVisibility, StatOwner);
	return _TryGetAllStats(StatType, Keys, Values);
}

bool UBeamStatsSubsystem::TryGetStat(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, FString StatKey, FString& Value)
{
	FBeamRealmUser OutRealmUser;
	if (UserSlots->GetUserDataAtSlot(Slot, OutRealmUser, this))
	{
		const auto StatType = UBeamStatsTypeLibrary::MakeStatsType(StatDomain, StatVisibility, OutRealmUser.GamerTag);
		return _TryGetStat(StatType, StatKey, Value);
	}
	return false;
}

bool UBeamStatsSubsystem::TryGetStatByGamerTag(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, FBeamGamerTag StatOwner, FString StatKey, FString& Value)
{
	const auto StatType = UBeamStatsTypeLibrary::MakeStatsType(StatDomain, StatVisibility, StatOwner);
	return _TryGetStat(StatType, StatKey, Value);
}


/* * STATS SUBSYSTEM - Operations * */

FBeamOperationHandle UBeamStatsSubsystem::RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshStats(UserSlot, Type, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshStats(UserSlot, Type, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::RefreshSingleStatOperation(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshSingleStat(UserSlot, Type, StatKey, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_RefreshSingleStatOperation(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshSingleStat(UserSlot, Type, StatKey, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CommitStatsOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitStats(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_CommitStatsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitStats(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::SetStatOperation(FUserSlot UserSlot, FString Key, FString Value, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SetStat(UserSlot, Key, Value, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_SetStatOperation(FUserSlot UserSlot, const FString& Key, const FString& Value, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SetStat(UserSlot, Key, Value, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::DeleteStatOperation(FUserSlot UserSlot, FString Key, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DeleteStat(UserSlot, Key, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_DeleteStatOperation(FUserSlot UserSlot, const FString& Key, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DeleteStat(UserSlot, Key, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::IncrementStatsOperation(FUserSlot UserSlot, const TMap<FString, int32>& Stats, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	IncrementStats(UserSlot, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_IncrementStatsOperation(FUserSlot UserSlot, const TMap<FString, int32>& Stats, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	IncrementStats(UserSlot, Stats, Handle);
	return Handle;
}


/* * STATS SUBSYSTEM - Operation Implementations * */

void UBeamStatsSubsystem::RefreshStats(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!IsRunningDedicatedServer())
	{
		if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	// Get the stat key for this user, if none is provided
	auto StatType = Type;
	if (UBeamStatsTypeLibrary::GetGamerTag(Type).AsString.IsEmpty())
	{
		StatType = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(Type, RealmUser.GamerTag);
	}

	auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, StatType](FGetClientFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType = StatType;

			// Prepare the stats updated event.
			FBeamStatsUpdatedEvent Evt;
			Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(StatType);
			Evt.LocalSlot = UserSlot;

			for (const auto& Stat : Resp.SuccessData->Stats)
			{
				const FString StatKey = Stat.Key;
				const FString NewStatValue = Stat.Value;

				FString OldValue;
				if (UserStatsState->StringStats.Contains(StatKey))
				{
					OldValue = UserStatsState->StringStats[StatKey];
					UserStatsState->StringStats[StatKey] = NewStatValue;
				}
				else
				{
					OldValue = FString("");
					UserStatsState->StringStats.Add(StatKey, NewStatValue);
				}

				Evt.OldValues.Add(StatKey, OldValue);
				Evt.NewValues.Add(StatKey, NewStatValue);
				UE_LOG(LogBeamStats, Verbose, TEXT("Updated Stats. STAT_KEY=%s, OLD=%s, NEW=%s"), *StatKey, *OldValue, *NewStatValue)
			}

			OnStatsUpdatedCode.Broadcast(Evt);
			OnStatsUpdated.Broadcast(Evt);
			UE_LOG(LogBeamStats, Display, TEXT("Updated Stats!"))
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestGetStats(UserSlot, Type, Op, Handler);
}

void UBeamStatsSubsystem::RefreshSingleStat(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot when running in clients.
	FBeamRealmUser RealmUser;
	if (!IsRunningDedicatedServer())
	{
		if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	// Get the stat key for this user, if none is provided
	auto StatType = Type;
	if (UBeamStatsTypeLibrary::GetGamerTag(Type).AsString.IsEmpty())
	{
		StatType = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(Type, RealmUser.GamerTag);
	}

	auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, StatType](FGetClientFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType = StatType;

			// Prepare the stats updated event.
			FBeamStatsUpdatedEvent Evt;
			Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(StatType);
			Evt.LocalSlot = UserSlot;

			for (const auto& Stat : Resp.SuccessData->Stats)
			{
				const FString StatKey = Stat.Key;
				const FString NewStatValue = Stat.Value;

				FString OldValue;
				if (UserStatsState->StringStats.Contains(StatKey))
				{
					OldValue = UserStatsState->StringStats[StatKey];
					UserStatsState->StringStats[StatKey] = NewStatValue;
				}
				else
				{
					OldValue = FString("");
					UserStatsState->StringStats.Add(StatKey, NewStatValue);
				}

				Evt.OldValues.Add(StatKey, OldValue);
				Evt.NewValues.Add(StatKey, NewStatValue);
				UE_LOG(LogBeamStats, Verbose, TEXT("Updated Stats. STAT_KEY=%s, OLD=%s, NEW=%s"), *StatKey, *OldValue, *NewStatValue)
			}

			OnStatsUpdatedCode.Broadcast(Evt);
			OnStatsUpdated.Broadcast(Evt);
			UE_LOG(LogBeamStats, Display, TEXT("Updated Stats!"))
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestGetSingleStat(UserSlot, Type, StatKey, Op, Handler);
}

void UBeamStatsSubsystem::CommitStats(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	// Get the command buffer that is being build.
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(UserSlot);

	// Get the stat key for this user
	auto Stat = CommandBuffer->StatType;
	checkf(UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag) == Stat, TEXT("Make sure to call this with the same user slot."))

	// Make the request and update the local cache if successful
	const auto StatNames = TArray<FString>(CommandBuffer->StatNames);
	const auto StatValues = TArray<FString>(CommandBuffer->StatValues);
	const auto SetStatHandler = FOnPostClientFullResponse::CreateLambda([this, Op, UserSlot, Stat, StatNames, StatValues](FPostClientFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(Stat, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType = Stat;

			FBeamStatsUpdatedEvent Evt;
			Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(Stat);
			Evt.LocalSlot = UserSlot;


			// Update the local cache from the command buffer.
			const auto StatSize = StatNames.Num();
			for (int i = 0; i < StatSize; ++i)
			{
				const FString StatKey = StatNames[i];
				const FString NewStatValue = StatValues[i];

				if (!StatKey.IsEmpty())
				{
					FString OldValue;
					if (UserStatsState->StringStats.Contains(StatKey))
					{
						OldValue = UserStatsState->StringStats[StatKey];
						UserStatsState->StringStats[StatKey] = NewStatValue;
					}
					else
					{
						OldValue = FString("");
						UserStatsState->StringStats.Add(StatKey, NewStatValue);
					}
					Evt.OldValues.Add(StatKey, OldValue);
					Evt.NewValues.Add(StatKey, NewStatValue);
				}
			}

			OnStatsUpdatedCode.Broadcast(Evt);
			OnStatsUpdated.Broadcast(Evt);

			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	FBeamRequestContext Ctx = RequestSetStats(CommandBuffer->UserSlot, CommandBuffer->AsMap(), Op, SetStatHandler);
	ResetUpdateCommand(UserSlot);
}

void UBeamStatsSubsystem::SetStat(FUserSlot Slot, FString StatKey, FString StatValue, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	// Get the stat key for this user
	auto Stat = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);

	// Make the request and update the local cache if successful
	const auto SetStatHandler = FOnPostClientFullResponse::CreateLambda([this, Op, Stat, StatKey, StatValue](FPostClientFullResponse Resp)
	{
		if (Resp.State == RS_Success)
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(Stat, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType = Stat;

			if (UserStatsState->StringStats.Contains(StatKey))
				UserStatsState->StringStats[StatKey] = StatValue;
			else
				UserStatsState->StringStats.Add(StatKey, StatValue);

			RequestTracker->TriggerOperationSuccess(Op, {});
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
	});
	FBeamRequestContext Ctx = RequestSetStats(Slot, {{StatKey, StatValue}}, Op, SetStatHandler);
}

void UBeamStatsSubsystem::DeleteStat(FUserSlot Slot, FString StatKey, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	// Get the stat key for this user
	auto Stat = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);

	// Make the request and update the local cache if successful
	const auto SetStatHandler = FOnDeleteStatsFullResponse::CreateLambda([this, Op, Stat, StatKey](FDeleteStatsFullResponse Resp)
	{
		if (Resp.State == RS_Success)
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(Stat, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType = Stat;

			if (UserStatsState->StringStats.Contains(StatKey))
				UserStatsState->StringStats.Remove(StatKey);

			RequestTracker->TriggerOperationSuccess(Op, {});
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
	});
	FBeamRequestContext Ctx = RequestDeleteStats(Slot, StatKey, Op, SetStatHandler);
}

void UBeamStatsSubsystem::IncrementStats(FUserSlot Slot, TMap<FString, int> StatIncrements, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	// Check that every one of the given stats are actually int stats	
	const auto Stat = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);
	{
		UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(Stat, NewObject<UBeamStatsState>());
		TArray<FString> NonIntegers;
		for (const auto& Increment : StatIncrements)
		{
			if (FString* ExistingStat = UserStatsState->StringStats.Find(Increment.Key))
			{
				if (!FDefaultValueHelper::IsStringValidInteger(*ExistingStat))
				{
					NonIntegers.Add(*ExistingStat);
				}
			}
		}

		// If we found any stat to not be an integer let's error this out. 
		if (NonIntegers.Num())
		{
			RequestTracker->TriggerOperationError(Op, FString::Join(NonIntegers, TEXT(",")));
			return;
		}
	}

	const auto IncrementStatHandler = FOnPostClientFullResponse::CreateLambda([this, Stat, StatIncrements, Op](FPostClientFullResponse Resp)
	{
		if (Resp.State == RS_Error)
		{
			UE_LOG(LogBeamStats, Error, TEXT("Failed to Increment Stat: %s"), *Resp.ErrorData.message)
			RequestTracker->TriggerOperationError(Op, TEXT("FAILED_TO_INCREMENT"));
			return;
		}

		if (Resp.State == RS_Cancelled)
		{
			RequestTracker->TriggerOperationCancelled(Op, TEXT("FAILED_TO_INCREMENT"));
			return;
		}

		if (Resp.State == RS_Success)
		{
			// Get the stat state for that key
			UBeamStatsState* State = PlayerStatCache.FindOrAdd(Stat, NewObject<UBeamStatsState>());
			State->OwnerType = Stat;

			for (const auto& StatIncrement : StatIncrements)
			{
				const FString AsStr = FString::Printf(TEXT("%d"), StatIncrement.Value);
				if (!State->StringStats.Contains(StatIncrement.Key))
				{
					State->StringStats.Add(StatIncrement.Key, AsStr);
				}
				else
				{
					const FString Curr = State->StringStats[StatIncrement.Key];
					int32 CurrValue = 0;
					checkf(FDefaultValueHelper::ParseInt(Curr, CurrValue), TEXT("You should never see this."))
					CurrValue += StatIncrement.Value;
					State->StringStats[StatIncrement.Key] = FString::Printf(TEXT("%d"), CurrValue);
				}
			}
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	FBeamRequestContext Ctx = RequestIncrementStats(Slot, StatIncrements, Op, IncrementStatHandler);
}


/* * STATS SUBSYSTEM - Request Helper Functions * */

FBeamRequestContext UBeamStatsSubsystem::RequestGetStats(const FUserSlot& UserSlot, FBeamStatsType StatsType, const FBeamOperationHandle Op, const FOnGetClientFullResponse Handler) const
{
	const auto Req = UGetClientRequest::Make(StatsType, FOptionalString(), GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_GetClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestGetSingleStat(const FUserSlot& UserSlot, FBeamStatsType StatsType, FString StatKey, const FBeamOperationHandle Op,
                                                              const FOnGetClientFullResponse Handler) const
{
	const auto Req = UGetClientRequest::Make(StatsType, FOptionalString(StatKey), GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_GetClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestGetStats(const FUserSlot& UserSlot, const TEnumAsByte<EBeamStatsDomain>& Domain, const TEnumAsByte<EBeamStatsVisibility>& Visibility,
                                                         const FBeamGamerTag& GamerTag, const FBeamOperationHandle Op,
                                                         const FOnGetClientFullResponse Handler) const
{
	const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Domain, Visibility, GamerTag);
	const auto Req = UGetClientRequest::Make(StatsType, FOptionalString(), GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_GetClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestSetStats(const FUserSlot& UserSlot, TMap<FString, FString> Stats, const FBeamOperationHandle Op, const FOnPostClientFullResponse Handler) const
{
	FBeamRealmUser RealmUser;
	checkf(UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this), TEXT("You must only call this function with an authenticated UserSlot"));

	const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);
	const auto Req = UPostClientRequest::Make(StatsType, FOptionalBool{}, FOptionalBeamStatsType{}, FOptionalMapOfString{Stats}, FOptionalMapOfString{}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_PostClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestIncrementStats(const FUserSlot& UserSlot, TMap<FString, int32> StatsToAdd, const FBeamOperationHandle Op, const FOnPostClientFullResponse Handler) const
{
	FBeamRealmUser RealmUser;
	checkf(UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this), TEXT("You must only call this function with an authenticated UserSlot"));

	TMap<FString, FString> Stats;
	Stats.Reserve(StatsToAdd.Num());
	for (const auto& ToAdd : StatsToAdd)
	{
		Stats.Add(ToAdd.Key, FString::Printf(TEXT("%d"), ToAdd.Value));
	}

	const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);
	const auto Req = UPostClientRequest::Make(StatsType, FOptionalBool{}, FOptionalBeamStatsType{}, FOptionalMapOfString{}, FOptionalMapOfString{Stats}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_PostClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestDeleteStats(const FUserSlot& UserSlot, FString StatName, const FBeamOperationHandle Op, const FOnDeleteStatsFullResponse Handler) const
{
	FBeamRealmUser RealmUser;
	checkf(UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this), TEXT("You must only call this function with an authenticated UserSlot"));

	const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);
	const auto Req = UDeleteStatsRequest::Make(StatsType, FOptionalString{StatName}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_DeleteStats(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}


/* * STATS SUBSYSTEM - Local Helper Functions * */

bool UBeamStatsSubsystem::_TryGetAllStats(FBeamStatsType Type, TArray<FString>& Keys, TArray<FString>& Values)
{
	if (const auto CachePtr = this->PlayerStatCache.Find(Type))
	{
		const auto Cache = *CachePtr;
		Cache->StringStats.GetKeys(Keys);
		for (const FString& Key : Keys)
		{
			Values.Add(Cache->StringStats[Key]);
		}
		return true;
	}
	return false;
}

bool UBeamStatsSubsystem::_TryGetStat(FBeamStatsType Type, FString StatKey, FString& Value)
{
	if (const auto CachePtr = this->PlayerStatCache.Find(Type))
	{
		const auto Cache = *CachePtr;
		if (const auto StatVal = Cache->StringStats.Find(StatKey))
		{
			Value = *StatVal;
			return true;
		}
	}
	return false;
}
