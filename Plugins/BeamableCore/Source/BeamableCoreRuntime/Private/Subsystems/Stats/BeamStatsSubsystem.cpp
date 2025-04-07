// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================


#include "Subsystems/Stats/BeamStatsSubsystem.h"

void UBeamStatUpdateCommand::Init(UBeamStatsSubsystem* Subsystem, FUserSlot Slot, FBeamStatsType Type, TMap<FString, FString> StartingStats, TMap<FString, double> StartingNumericStats)
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

	NumericStatNames.Reserve(StartingNumericStats.Num());
	NumericStatValues.Reserve(StartingNumericStats.Num());
	for (auto StartingStat : StartingNumericStats)
	{
		NumericStatNames.Add(StartingStat.Key);
		NumericStatValues.Add(StartingStat.Value);
	}
}

void UBeamStatUpdateCommand::AddStat(FString Key, FString Value)
{
	StatsSubsystem->AddStatToUpdateCommand(StatType, Key, Value);
}

void UBeamStatUpdateCommand::AddNumericStat(FString Key, double Value)
{
	StatsSubsystem->AddNumericStatToUpdateCommand(StatType, Key, Value);
}

void UBeamStatUpdateCommand::AddStats(TArray<FString> Key, TArray<FString> Value)
{
	ensureAlwaysMsgf(Key.Num() == Value.Num(), TEXT("Key and Value arrays must be parallel. KEY_NUM=%d, VALUE_NUM=%d"), Key.Num(), Value.Num());

	for (int i = 0; i < Key.Num(); ++i) StatsSubsystem->AddStatToUpdateCommand(StatType, Key[i], Value[i]);
}

void UBeamStatUpdateCommand::AddNumericStats(TArray<FString> Key, TArray<double> Value)
{
	ensureAlwaysMsgf(Key.Num() == Value.Num(), TEXT("Key and Value arrays must be parallel. KEY_NUM=%d, VALUE_NUM=%d"), Key.Num(), Value.Num());

	for (int i = 0; i < Key.Num(); ++i) StatsSubsystem->AddNumericStatToUpdateCommand(StatType, Key[i], Value[i]);
}


void UBeamStatUpdateCommand::AddStatsMap(TMap<FString, FString> Stats)
{
	for (const auto& Stat : Stats) StatsSubsystem->AddStatToUpdateCommand(StatType, Stat.Key, Stat.Value);
}

void UBeamStatUpdateCommand::AddNumericStatsMap(TMap<FString, double> Stats)
{
	for (const auto& Stat : Stats) StatsSubsystem->AddNumericStatToUpdateCommand(StatType, Stat.Key, Stat.Value);
}


void UBeamStatUpdateCommand::RemoveStat(FString Key)
{
	StatsSubsystem->RemoveStatFromUpdateCommand(StatType, Key);
}

void UBeamStatUpdateCommand::Discard()
{
	StatsSubsystem->ResetUpdateCommand(StatType);
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

TMap<FString, double> UBeamStatUpdateCommand::AsNumericMap()
{
	TMap<FString, double> Map;
	check(NumericStatNames.Num() == NumericStatValues.Num())

	for (int i = 0; i < NumericStatNames.Num(); ++i)
	{
		const FString Key = NumericStatNames[i];
		const double Val = NumericStatValues[i];

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

bool UBeamStatsSubsystem::TryCreateUpdateCommand(FUserSlot Slot, const FBeamStatsType& StatType, const TMap<FString, FString>& Stats, const TMap<FString, double> NumericStats, UBeamStatUpdateCommand*& Command)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		if (!IsRunningDedicatedServer())
		{
			Command = nullptr;
			return false;
		}
	}

	// Let's build the correct stat type...
	auto Type = StatType;
	if (UBeamStatsTypeLibrary::GetGamerTag(StatType).AsString.IsEmpty())
	{
		if (!IsRunningDedicatedServer())
		{
			Type = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(Type, RealmUser.GamerTag);
		}
		else
		{
			UE_LOG(LogBeamStats, Error, TEXT("No GamerTag provided so we can't create the UpdateCommand."))
			return false;
		}
	}

	// Let's do some validation with regards to write permissions:
	// - Client|Public, writable by owner user and server.
	// - Client|Private, writable by owner user and server.
	// - Game|Public, writable by server.
	// - Game|Private, writable by server.
	TEnumAsByte Domain = EBeamStatsDomain::Client;
	TEnumAsByte Visibility = EBeamStatsVisibility::Private;
	FBeamGamerTag GamerTag;
	UBeamStatsTypeLibrary::BreakStatsType(StatType, Domain, Visibility, GamerTag);
	if (!IsRunningDedicatedServer())
	{
		if (!ensureAlwaysMsgf(Domain == Client, TEXT("Cannot write to Game stats from non-dedicated server environments.")))
			return false;

		if (!ensureAlwaysMsgf(GamerTag == RealmUser.GamerTag, TEXT("Cannot write to stats other than the authenticated user's from non-dedicated server environments.")))
			return false;
	}

	// If we already have a command for this stat type, error.
	if (UpdateCommands.Contains(Type))
	{
		UE_LOG(LogBeamStats, Error, TEXT("Trying to start a new update command while one is building."))
		Command = nullptr;
		return false;
	}

	// Create a new update command buffer from it.
	Command = NewObject<UBeamStatUpdateCommand>(GetTransientPackage());
	Command->Init(this, Slot, Type, Stats, NumericStats);

	UpdateCommands.Add(Type, Command);
	return true;
}

void UBeamStatsSubsystem::AddStatToUpdateCommand(FBeamStatsType StatType, FString Key, FString Value)
{
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(StatType);
	const int32 Idx = CommandBuffer->StatNames.AddUnique(Key);

	if (const bool bWasNewStat = Idx == CommandBuffer->StatValues.Num())
		CommandBuffer->StatValues.AddUninitialized();

	CommandBuffer->StatValues[Idx] = Value;
}

void UBeamStatsSubsystem::AddNumericStatToUpdateCommand(FBeamStatsType StatType, FString Key, double Value)
{
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(StatType);
	const int32 Idx = CommandBuffer->NumericStatNames.AddUnique(Key);

	if (const bool bWasNewStat = Idx == CommandBuffer->NumericStatValues.Num())
		CommandBuffer->NumericStatValues.AddUninitialized();

	CommandBuffer->NumericStatValues[Idx] = Value;
}

void UBeamStatsSubsystem::RemoveStatFromUpdateCommand(FBeamStatsType StatType, FString Key)
{
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(StatType);
	auto Idx = CommandBuffer->StatNames.Find(Key);
	if (Idx != INDEX_NONE)
	{
		CommandBuffer->StatNames.RemoveAt(Idx);
		CommandBuffer->StatValues.RemoveAt(Idx);
	}

	Idx = CommandBuffer->NumericStatNames.Find(Key);
	if (Idx != INDEX_NONE)
	{
		CommandBuffer->NumericStatNames.RemoveAt(Idx);
		CommandBuffer->NumericStatValues.RemoveAt(Idx);
	}
}

void UBeamStatsSubsystem::ResetUpdateCommand(FBeamStatsType StatType)
{
	UpdateCommands.Remove(StatType);
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

void UBeamStatsSubsystem::RefreshAllStats(FUserSlot UserSlot, FBeamGamerTag GamerTag, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot for the non-dedicated server case.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		if (!IsRunningDedicatedServer())
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	// Handle the case where no GamerTag was provided.
	if (GamerTag.AsString.IsEmpty())
	{
		if (!IsRunningDedicatedServer())
		{
			GamerTag = RealmUser.GamerTag;
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAMER_TAG_PROVIDED"));
			return;
		}
	}

	const auto bIsFetchingForAuthenticatedUser = RealmUser.GamerTag == GamerTag;

	const auto bShouldFetchClientPublic = true;
	const auto bShouldFetchClientPrivate = bIsFetchingForAuthenticatedUser || IsRunningDedicatedServer();
	const auto bShouldFetchGamePublic = IsRunningDedicatedServer();
	const auto bShouldFetchGamePrivate = IsRunningDedicatedServer();

	TArray<FBeamRequestContext> Requests;
	if (bShouldFetchClientPublic)
	{
		auto StatType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, GamerTag);
		auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, GamerTag, StatType](FGetClientFullResponse Resp)
		{
			// If we are invoking this before retrying, we just don't do anything 
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
				UserStatsState->OwnerType = StatType;

				// Prepare the stats updated event.
				FBeamStatsUpdatedEvent Evt;
				Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(StatType);
				Evt.LocalSlot = UserSlot;
				Evt.StatType = StatType;

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
				UE_LOG(LogBeamStats, Display, TEXT("Refreshed Client|Public Stats for User. GAMER_TAG=%s"), *GamerTag.AsString)
			}
		});

		auto Ctx = RequestGetStats(UserSlot, StatType, Op, Handler);
		Requests.Add(Ctx);
	}

	// Make the request to fetch Client|Private stats if we should
	if (bShouldFetchClientPrivate)
	{
		auto StatType = UBeamStatsTypeLibrary::MakeStatsType(Client, Private, GamerTag);
		auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, GamerTag, StatType](FGetClientFullResponse Resp)
		{
			// If we are invoking this before retrying, we just don't do anything 
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
				UserStatsState->OwnerType = StatType;

				// Prepare the stats updated event.
				FBeamStatsUpdatedEvent Evt;
				Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(StatType);
				Evt.LocalSlot = UserSlot;
				Evt.StatType = StatType;

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
				UE_LOG(LogBeamStats, Display, TEXT("Refreshed Client|Private Stats for User. GAMER_TAG=%s"), *GamerTag.AsString)
			}
		});

		auto Ctx = RequestGetStats(UserSlot, StatType, Op, Handler);
		Requests.Add(Ctx);
	}

	// Make the request to fetch Game Public stats, if we should
	if (bShouldFetchGamePublic)
	{
		checkf(IsRunningDedicatedServer(), TEXT("This should only ever run when inside dedicated servers!"))
		auto StatType = UBeamStatsTypeLibrary::MakeStatsType(Game, Public, GamerTag);
		auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, GamerTag, StatType](FGetClientFullResponse Resp)
		{
			// If we are invoking this before retrying, we just don't do anything 
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
				UserStatsState->OwnerType = StatType;

				// Prepare the stats updated event.
				FBeamStatsUpdatedEvent Evt;
				Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(StatType);
				Evt.LocalSlot = UserSlot;
				Evt.StatType = StatType;

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
				UE_LOG(LogBeamStats, Display, TEXT("Refreshed Game|Public Stats for User. GAMER_TAG=%s"), *GamerTag.AsString)
			}
		});

		auto Ctx = RequestGetStats(UserSlot, StatType, Op, Handler);
		Requests.Add(Ctx);
	}

	// Make the request to fetch Game Private stats, if we should
	if (bShouldFetchGamePrivate)
	{
		checkf(IsRunningDedicatedServer(), TEXT("This should only ever run when inside dedicated servers!"))
		auto StatType = UBeamStatsTypeLibrary::MakeStatsType(Game, Private, GamerTag);
		auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, GamerTag, StatType](FGetClientFullResponse Resp)
		{
			// If we are invoking this before retrying, we just don't do anything 
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
				UserStatsState->OwnerType = StatType;

				// Prepare the stats updated event.
				FBeamStatsUpdatedEvent Evt;
				Evt.GamerTag = UBeamStatsTypeLibrary::GetGamerTag(StatType);
				Evt.LocalSlot = UserSlot;
				Evt.StatType = StatType;

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
				UE_LOG(LogBeamStats, Display, TEXT("Refreshed Game|Private Stats for User. GAMER_TAG=%s"), *GamerTag.AsString)
			}
		});

		auto Ctx = RequestGetStats(UserSlot, StatType, Op, Handler);
		Requests.Add(Ctx);
	}

	// Wait for all the requests to complete and trigger the operation as a success/error.
	RequestTracker->CPP_WaitAll(Requests, {}, {}, FOnWaitCompleteCode::CreateLambda([this, UserSlot, GamerTag, Op](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> Errs;
		if (RequestTracker->IsWaitFailed(Evt, Errs))
		{
			UE_LOG(LogBeamStats, Error, TEXT("Failed Stat Refresh. ERRORS=%s"), *FString::Join(Errs, TEXT(", ")))
			RequestTracker->TriggerOperationError(Op, TEXT("FAILED_STAT_REFRESH"));
			return;
		}

		RequestTracker->TriggerOperationSuccess(Op, {});
	}));
}

void UBeamStatsSubsystem::RefreshStats(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot for the non-dedicated server case.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		if (!IsRunningDedicatedServer())
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	// Handle the case where no GamerTag was provided.
	auto StatType = Type;
	if (UBeamStatsTypeLibrary::GetGamerTag(Type).AsString.IsEmpty())
	{
		if (!IsRunningDedicatedServer())
		{
			StatType = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(Type, RealmUser.GamerTag);
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAMER_TAG_PROVIDED"));
			return;
		}
	}

	// Let's do some validation:
	// - if we are not in a dedicated server environment, we are not allowed to read 'Game' stats.
	// - if we are not in a dedicated server environment, we are not allowed to read Client Private stats for clients that are NOT the authenticated user.
	TEnumAsByte Domain = EBeamStatsDomain::Client;
	TEnumAsByte Visibility = EBeamStatsVisibility::Private;
	FBeamGamerTag GamerTag;
	UBeamStatsTypeLibrary::BreakStatsType(StatType, Domain, Visibility, GamerTag);
	if (!IsRunningDedicatedServer())
	{
		if (Domain == Game)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_READ_PERMISSION"));
			return;
		}
		if (Visibility == Private && RealmUser.GamerTag != GamerTag)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_READ_PERMISSION"));
			return;
		}
	}

	auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, StatType, Domain, Visibility, GamerTag](FGetClientFullResponse Resp)
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

			UE_LOG(LogBeamStats, Display, TEXT("Refreshed %s|%s Stats for User. GAMER_TAG=%s"),
			       *StaticEnum<EBeamStatsDomain>()->GetNameStringByValue(Domain),
			       *StaticEnum<EBeamStatsVisibility>()->GetNameStringByValue(Visibility),
			       *GamerTag.AsString)

			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestGetStats(UserSlot, Type, Op, Handler);
}

void UBeamStatsSubsystem::RefreshSingleStat(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot for the non-dedicated server case.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		if (!IsRunningDedicatedServer())
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	// Handle the case where no GamerTag was provided.
	auto StatType = Type;
	if (UBeamStatsTypeLibrary::GetGamerTag(Type).AsString.IsEmpty())
	{
		if (!IsRunningDedicatedServer())
		{
			StatType = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(Type, RealmUser.GamerTag);
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAMER_TAG_PROVIDED"));
			return;
		}
	}

	// Let's do some validation:
	// - if we are not in a dedicated server environment, we are not allowed to read 'Game' stats.
	// - if we are not in a dedicated server environment, we are not allowed to read Client Private stats for clients that are NOT the authenticated user.
	TEnumAsByte Domain = EBeamStatsDomain::Client;
	TEnumAsByte Visibility = EBeamStatsVisibility::Private;
	FBeamGamerTag GamerTag;
	UBeamStatsTypeLibrary::BreakStatsType(StatType, Domain, Visibility, GamerTag);
	if (!IsRunningDedicatedServer())
	{
		if (Domain == Game)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_READ_PERMISSION"));
			return;
		}
		if (Visibility == Private && RealmUser.GamerTag != GamerTag)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_READ_PERMISSION"));
			return;
		}
	}

	auto Handler = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, StatType, Domain, Visibility, GamerTag](FGetClientFullResponse Resp)
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
			Evt.StatType = StatType;

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
			UE_LOG(LogBeamStats, Display, TEXT("Refreshed %s|%s Stats for User. GAMER_TAG=%s"),
			       *StaticEnum<EBeamStatsDomain>()->GetNameStringByValue(Domain),
			       *StaticEnum<EBeamStatsVisibility>()->GetNameStringByValue(Visibility),
			       *GamerTag.AsString)
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestGetSingleStat(UserSlot, Type, StatKey, Op, Handler);
}

void UBeamStatsSubsystem::CommitStats(UBeamStatUpdateCommand* UpdateCommand, FBeamOperationHandle Op)
{
	const auto UserSlot= UpdateCommand->UserSlot;
	auto StatType = UpdateCommand->StatType;
	
	// Ensure we have a user at the given slot for the non-dedicated server case.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		if (!IsRunningDedicatedServer())
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	// Handle the case where no GamerTag was provided.	
	if (UBeamStatsTypeLibrary::GetGamerTag(StatType).AsString.IsEmpty())
	{
		if (!IsRunningDedicatedServer())
		{
			StatType = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(StatType, RealmUser.GamerTag);
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAMER_TAG_PROVIDED"));
			return;
		}
	}
	
	// Let's do some validation:
	// - if we are not in a dedicated server environment, we are not allowed to read 'Game' stats.
	// - if we are not in a dedicated server environment, we are not allowed to read Client Private stats for clients that are NOT the authenticated user.
	TEnumAsByte Domain = EBeamStatsDomain::Client;
	TEnumAsByte Visibility = EBeamStatsVisibility::Private;
	FBeamGamerTag GamerTag;
	UBeamStatsTypeLibrary::BreakStatsType(StatType, Domain, Visibility, GamerTag);
	if (!IsRunningDedicatedServer())
	{
		if (Domain == Game)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_READ_PERMISSION"));
			return;
		}
		if (Visibility == Private && RealmUser.GamerTag != GamerTag)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_READ_PERMISSION"));
			return;
		}
	}
	
	// Get the stat key for this user
	auto Stat = UpdateCommand->StatType;	

	// Make the request and update the local cache if successful
	const auto StatNames = TArray<FString>(UpdateCommand->StatNames);
	const auto StatValues = TArray<FString>(UpdateCommand->StatValues);
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

	FBeamRequestContext Ctx = RequestSetStats(UpdateCommand->UserSlot, UpdateCommand->AsMap(), Op, SetStatHandler);
	ResetUpdateCommand(StatType);
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
