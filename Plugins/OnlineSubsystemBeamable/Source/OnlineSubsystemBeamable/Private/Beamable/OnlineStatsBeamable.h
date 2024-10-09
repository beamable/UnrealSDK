#pragma once

#include "CoreMinimal.h"
#include "Beamable/OnlineSubsystemBeamable.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "UObject/Object.h"

/**
 * Interface for interacting with Beamable stats
 */
class FOnlineStatsBeamable : public IOnlineStats
                             , public TSharedFromThis<FOnlineStatsBeamable, ESPMode::ThreadSafe>
{
public:
	FOnlineStatsBeamable() = delete;
	virtual ~FOnlineStatsBeamable() = default;

	// IOnlineStats Interface
	virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const FUniqueNetIdRef StatsUser, const FOnlineStatsQueryUserStatsComplete& Delegate) override;

	virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const TArray<FUniqueNetIdRef>& StatUsers, const TArray<FString>& StatNames, const FOnlineStatsQueryUsersStatsComplete& Delegate) override;
	
	virtual TSharedPtr<const FOnlineStatsUserStats> GetStats(const FUniqueNetIdRef StatsUserId) const override;
	virtual void UpdateStats(const FUniqueNetIdRef LocalUserId, const TArray<FOnlineStatsUserUpdatedStats>& UpdatedUserStats, const FOnlineStatsUpdateStatsComplete& Delegate) override;
#if !UE_BUILD_SHIPPING
	virtual void ResetStats(const FUniqueNetIdRef StatsUserId) override;
#endif
	// ~IOnlineStats Interface

	void OnStatsUpdated(FBeamStatsUpdatedEvent BeamStatsUpdatedEvent);
	FOnlineStatsBeamable(FOnlineSubsystemBeamable* InSubsystem);

private:
	// void WriteStats(EOS_ProductUserId LocalUserId, EOS_ProductUserId UserId, const FOnlineStatsUserUpdatedStats& PlayerStats);

	/** Reference to the main Beamable subsystem */
	FOnlineSubsystemBeamable* BeamableSubsystem;

	/** Cached list of stats for users as they arrive */
	TUniqueNetIdMap<TSharedRef<FOnlineStatsUserStats>> StatsCache;
	TUniqueNetIdMap<FDelegateHandle> StatsUpdatedDelegates;

	UBeamStatsSubsystem* StatsSubsystem;

	void Initialize(const FUniqueNetIdRef& UniqueNetId);
};

typedef TSharedPtr<FOnlineStatsBeamable, ESPMode::ThreadSafe> FOnlineStatsBeamablePtr;
typedef TWeakPtr<FOnlineStatsBeamable, ESPMode::ThreadSafe> FOnlineStatsBeamableWeakPtr;
