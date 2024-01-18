// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================


#include "Subsystems/Stats/BeamStatsSubsystem.h"

void UBeamStatUpdateCommand::Init(UBeamStatsSubsystem* Subsystem, FUserSlot Slot, FBeamStatsType Type, TMap<FString, FString> StartingStats)
{
	StatsSubsystem = Subsystem;
	UserSlot       = Slot;
	StatType       = Type;

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
	UserSlots      = Runtime->UserSlotSystem;
	RequestTracker = Runtime->RequestTrackerSystem;
	StatsApi       = GEngine->GetEngineSubsystem<UBeamStatsApi>();
}

void UBeamStatsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBeamStatsSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	const FBeamGamerTag UserGamerTag = BeamRealmUser.GamerTag;

	const UEnum* DomainEnum     = StaticEnum<EBeamStatsDomain>();
	const UEnum* VisibilityEnum = StaticEnum<EBeamStatsVisibility>();
	for (int i = 0; i < DomainEnum->NumEnums(); ++i)
	{
		EBeamStatsDomain Domain = static_cast<EBeamStatsDomain>(DomainEnum->GetValueByIndex(i));
		for (int i2 = 0; i2 < VisibilityEnum->NumEnums(); ++i2)
		{
			EBeamStatsVisibility Visibility = static_cast<EBeamStatsVisibility>(VisibilityEnum->GetValueByIndex(i2));
			FBeamStatsType       Type       = UBeamStatsTypeLibrary::MakeStatsType(Domain, Visibility, UserGamerTag);

			UBeamStatsState* UserStatsState = NewObject<UBeamStatsState>();
			UserStatsState->OwnerType       = Type;
			PlayerStatCache.Add(Type, UserStatsState);
		}
	}

	FBeamStatsType ClientPublicStats = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, UserGamerTag);
	ResultOp = RefreshStatsOperation(UserSlot, ClientPublicStats, {}, this);	
}

void UBeamStatsSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	FBeamRealmUser RealmUser;
	checkf(UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this), TEXT("This should be impossible!"));

	// Let's just stop keeping a cache for each possible user key when they log out.
	const FBeamGamerTag UserGamerTag   = RealmUser.GamerTag;
	const UEnum*        DomainEnum     = StaticEnum<EBeamStatsDomain>();
	const UEnum*        VisibilityEnum = StaticEnum<EBeamStatsVisibility>();
	for (int i = 0; i < DomainEnum->NumEnums(); ++i)
	{
		const auto Domain = static_cast<EBeamStatsDomain>(DomainEnum->GetValueByIndex(i));
		for (int i2 = 0; i2 < VisibilityEnum->NumEnums(); ++i2)
		{
			const auto Visibility = static_cast<EBeamStatsVisibility>(VisibilityEnum->GetValueByIndex(i2));
			auto       Type       = UBeamStatsTypeLibrary::MakeStatsType(Domain, Visibility, UserGamerTag);
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
	const int32             Idx           = CommandBuffer->StatNames.AddUnique(Key);

	if (const bool bWasNewStat = Idx == CommandBuffer->StatNames.Num() - 1)
		CommandBuffer->StatValues.AddUninitialized();

	CommandBuffer->StatValues[Idx] = Value;
}

void UBeamStatsSubsystem::RemoveStatFromUpdateCommand(FUserSlot Slot, FString Key)
{
	UBeamStatUpdateCommand* CommandBuffer = UpdateCommands.FindChecked(Slot);
	const int32             Idx           = CommandBuffer->StatNames.Find(Key);
	CommandBuffer->StatNames.RemoveAt(Idx);
	CommandBuffer->StatValues.RemoveAt(Idx);
}

void UBeamStatsSubsystem::ResetUpdateCommand(FUserSlot Slot)
{
	UpdateCommands.Remove(Slot);
}

/* * STATS SUBSYSTEM - Operations * */

FBeamOperationHandle UBeamStatsSubsystem::RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshStats(UserSlot, Type, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshStats(UserSlot, Type, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CommitStatsOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitStats(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_CommitStatsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitStats(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::SetStatOperation(FUserSlot UserSlot, FString Key, FString Value, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SetStat(UserSlot, Key, Value, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStatsSubsystem::CPP_SetStatOperation(FUserSlot UserSlot, const FString& Key, const FString& Value, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SetStat(UserSlot, Key, Value, Handle);
	return Handle;
}


/* * STATS SUBSYSTEM - Operation Implementations * */

void UBeamStatsSubsystem::RefreshStats(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	// Get the stat key for this user
	auto StatType = UBeamStatsTypeLibrary::CopyStatsTypeWithGamerTag(Type, RealmUser.GamerTag);
	auto Handler  = FOnGetClientFullResponse::CreateLambda([this, Op, UserSlot, StatType](FGetClientFullResponse Resp)
	{
		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(StatType, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType       = StatType;

			// Prepare the stats updated event.
			FBeamStatsUpdatedEvent Evt;
			Evt.GamerTag  = UBeamStatsTypeLibrary::GetGamerTag(StatType);
			Evt.LocalSlot = UserSlot;

			for (const auto& Stat : Resp.SuccessData->Stats)
			{
				const FString StatKey      = Stat.Key;
				const FString NewStatValue = Stat.Value;

				FString OldValue;
				if (UserStatsState->StringStats.Contains(StatKey))
				{
					OldValue                             = UserStatsState->StringStats[StatKey];
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
	const auto SetStatHandler = FOnPostClientFullResponse::CreateLambda([this, Op, UserSlot, Stat, CommandBuffer](FPostClientFullResponse Resp)
	{
		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			UBeamStatsState* UserStatsState = PlayerStatCache.FindOrAdd(Stat, NewObject<UBeamStatsState>());
			UserStatsState->OwnerType       = Stat;

			FBeamStatsUpdatedEvent Evt;
			Evt.GamerTag  = UBeamStatsTypeLibrary::GetGamerTag(Stat);
			Evt.LocalSlot = UserSlot;

			// Update the local cache from the command buffer.
			for (int i = 0; i < CommandBuffer->StatNames.Num(); ++i)
			{
				const FString StatKey      = CommandBuffer->StatNames[i];
				const FString NewStatValue = CommandBuffer->StatValues[i];

				FString OldValue;
				if (UserStatsState->StringStats.Contains(StatKey))
				{
					OldValue                             = UserStatsState->StringStats[StatKey];
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

			UpdateCommands.Remove(UserSlot);

			OnStatsUpdatedCode.Broadcast(Evt);
			OnStatsUpdated.Broadcast(Evt);			

			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	FBeamRequestContext Ctx = RequestSetStats(CommandBuffer->UserSlot, CommandBuffer->AsMap(), Op, SetStatHandler);
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
			UserStatsState->OwnerType       = Stat;

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


/* * STATS SUBSYSTEM - Request Helper Functions * */

FBeamRequestContext UBeamStatsSubsystem::RequestGetStats(const FUserSlot& UserSlot, FBeamStatsType StatsType, const FBeamOperationHandle Op, const FOnGetClientFullResponse Handler) const
{
	const auto          Req = UGetClientRequest::Make(StatsType, FOptionalString(), GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_GetClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestGetStats(const FUserSlot& UserSlot, const TEnumAsByte<EBeamStatsDomain>& Domain, const TEnumAsByte<EBeamStatsVisibility>& Visibility, const FBeamGamerTag& GamerTag, const FBeamOperationHandle Op, const FOnGetClientFullResponse Handler) const
{
	const auto          StatsType = UBeamStatsTypeLibrary::MakeStatsType(Domain, Visibility, GamerTag);
	const auto          Req       = UGetClientRequest::Make(StatsType, FOptionalString(), GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_GetClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamStatsSubsystem::RequestSetStats(const FUserSlot& UserSlot, TMap<FString, FString> Stats, const FBeamOperationHandle Op, const FOnPostClientFullResponse Handler) const
{
	FBeamRealmUser RealmUser;
	checkf(UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this), TEXT("You must only call this function with an authenticated UserSlot"));

	const auto          StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, RealmUser.GamerTag);
	const auto          Req       = UPostClientRequest::Make(StatsType, FOptionalBool{}, FOptionalBeamStatsType{}, FOptionalMapOfString{Stats}, FOptionalMapOfString{}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	StatsApi->CPP_PostClient(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}
