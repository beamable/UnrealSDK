#include "Beamable/OnlineStatsBeamable.h"

#include "OnlineError.h"
#include "OnlineIdentityBeamable.h"
#include "Beamable/OnlineSubsystemBeamableTypes.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"

FOnlineStatsBeamable::FOnlineStatsBeamable(FOnlineSubsystemBeamable* InSubsystem) : BeamableSubsystem(InSubsystem)
{
}

void FOnlineStatsBeamable::Initialize(const FUniqueNetIdRef& UniqueNetId)
{
	if (StatsUpdatedDelegates.Contains(UniqueNetId))
		return;

	StatsSubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>();
	StatsUpdatedDelegates.Add(UniqueNetId, StatsSubsystem->OnStatsUpdatedCode.AddRaw(this, &FOnlineStatsBeamable::OnStatsUpdated));
}

void FOnlineStatsBeamable::OnStatsUpdated(FBeamStatsUpdatedEvent Event)
{
	auto Id = FUniqueNetIdBeamable::Create(Event.GamerTag.AsString);

	auto MyStats = StatsCache.Find(Id);
	if (!MyStats)
	{
		TSharedRef<FOnlineStatsUserStats> Stats = MakeShared<FOnlineStatsUserStats>(Id);

		for (auto Stat : Event.NewValues)
		{
			Stats->Stats.Add(Stat);
		}

		StatsCache.Add(Id, Stats);
	}
	else
	{
		for (auto Stat : Event.NewValues)
		{
			MyStats->Get().Stats.Add(Stat);
		}
	}
}

TSharedPtr<const FOnlineStatsUserStats> FOnlineStatsBeamable::GetStats(const FUniqueNetIdRef StatsUserId) const
{
	FBeamGamerTag StatsGamerTag = FBeamGamerTag(StatsUserId->ToString());
	const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, StatsGamerTag);
	FString IdString = FString(StatsUserId->ToString());
	auto Id = FUniqueNetIdBeamable::Create(IdString);
	auto Stats = StatsCache.Find(Id);
	if(Stats)
	{
		return Stats->ToSharedPtr();
	}
	
	return nullptr;
}

void FOnlineStatsBeamable::QueryStats(const FUniqueNetIdRef LocalUserId, const FUniqueNetIdRef StatsUser, const FOnlineStatsQueryUserStatsComplete& Delegate)
{
	Initialize(LocalUserId);

	FBeamGamerTag StatsGamerTag = FBeamGamerTag(StatsUser->ToString());
	const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, StatsGamerTag);

	const FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([&, Delegate, StatsUser](FBeamOperationEvent Evt)
	{
		FString IdString = FString(StatsUser->ToString());
		auto Id = FUniqueNetIdBeamable::Create(IdString);
		auto UserStats = StatsCache.Find(Id);
		// TODO: Brent -- need to handle the case where the stats are not found

		if (UserStats)
		{
			Delegate.ExecuteIfBound(FOnlineError::Success(), *UserStats);
		}
		else
		{
			Delegate.ExecuteIfBound(FOnlineError::Success(), nullptr);
		}
	});

	StatsSubsystem->CPP_RefreshStatsOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), StatsType, Handler);
}

void FOnlineStatsBeamable::QueryStats(const FUniqueNetIdRef LocalUserId, const TArray<FUniqueNetIdRef>& StatUsers, const TArray<FString>& StatNames, const FOnlineStatsQueryUsersStatsComplete& Delegate)
{
	Initialize(LocalUserId);
	const auto RequestTracker = BeamableSubsystem->GetRequestTracker();

	auto UserSlot = BeamableSubsystem->GetAccountForId(*LocalUserId)->CurrentSlot;

	TArray<FBeamOperationHandle> Operations;

	for (const auto& TargetUser : StatUsers)
	{
		const auto GamerTag = BeamableSubsystem->GetAccountForId(*TargetUser)->BeamUser.GamerTag;
		const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, GamerTag);

		// If no stat names are given, we'll fetch all the Client/Public stats for the given users.
		if (!StatNames.Num())
		{
			Operations.Add(StatsSubsystem->CPP_RefreshStatsOperation(UserSlot, StatsType, {}));
		}
		// If stat names are provided, we'll fetch them individually for each user.
		// TODO: Once we have a batch endpoint, replace this with that call.
		else
		{
			for (const auto& StatName : StatNames)
			{
				Operations.Add(StatsSubsystem->CPP_RefreshSingleStatOperation(UserSlot, StatsType, StatName, {}));
			}
		}
	}

	// Wait for all the refresh operations and trigger the delegate that was provided.
	RequestTracker->CPP_WaitAll({}, Operations, {}, FOnWaitCompleteCode::CreateLambda([this, RequestTracker, StatUsers, Delegate](const FBeamWaitCompleteEvent& Evt)
	{
		TArray<FString> Errs;
		if (RequestTracker->IsWaitFailed(Evt, Errs))
		{
			Delegate.ExecuteIfBound(FOnlineError::CreateError(FString(TEXT("Stats")), EOnlineErrorResult::FailExtended, "FAILED_REFRESH_STATS", FText::FromString(FString::Join(Errs, TEXT(",")))), {});
			return;
		}

		TArray<TSharedRef<const FOnlineStatsUserStats>> Stats;
		for (int i = 0; i < StatUsers.Num(); ++i)
		{
			auto UserStats = StatsCache.Find(StatUsers[i]);
			if (UserStats)
			{
				Stats.Add(*UserStats);
			}
			else
			{
				Delegate.ExecuteIfBound(FOnlineError::Success(), {});
			}
		}

		Delegate.ExecuteIfBound(FOnlineError::Success(), Stats);
	}));
}

void FOnlineStatsBeamable::UpdateStats(const FUniqueNetIdRef LocalUserId, const TArray<FOnlineStatsUserUpdatedStats>& UpdatedUserStats, const FOnlineStatsUpdateStatsComplete& Delegate)
{
	Initialize(LocalUserId);
	for (auto Account : UpdatedUserStats)
	{
		auto UserSlot = BeamableSubsystem->GetAccountForId(*LocalUserId)->CurrentSlot;
		TMap<FString, FString> Stats;

		for (auto Stat : Account.Stats)
		{
			Stats.Add(Stat.Key, Stat.Value.ToString());
		}

		UBeamStatUpdateCommand* Command = nullptr;
		if (StatsSubsystem->TryCreateUpdateCommand(UserSlot, Stats, Command))
		{
			StatsSubsystem->CPP_CommitStatsOperation(UserSlot, FBeamOperationEventHandlerCode::CreateLambda([&, Delegate](FBeamOperationEvent Evt)
			{
				Delegate.ExecuteIfBound(FOnlineError::Success());
			}));
		}
		else
		{
			UE_LOG(LogStats, Error, TEXT("FOnlineStatsBeamable::UpdateStats -- Failed to create update command for stats"));
		}
	}
}

#if !UE_BUILD_SHIPPING
void FOnlineStatsBeamable::ResetStats(const FUniqueNetIdRef StatsUserId)
{
}
#endif
