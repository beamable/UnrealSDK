#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemBeamableDefines.h"
#include "Misc/ConfigCacheIni.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "UserSlots/BeamUserSlots.h"
#include "UserSlots/UserSlot.h"

namespace FNetworkProtocolTypes
{
	const FLazyName Beamable(TEXT("Beamable"));
}


/** Forward declarations of all interface classes */
typedef TSharedPtr<class FOnlineIdentityBeamable, ESPMode::ThreadSafe> FOnlineIdentityBeamablePtr;
typedef TSharedPtr<class FOnlineSessionBeamable, ESPMode::ThreadSafe> FOnlineSessionBeamablePtr;
typedef TSharedPtr<class FOnlineFriendsBeamable, ESPMode::ThreadSafe> FOnlineFriendsBeamablePtr;
typedef TSharedPtr<class FMatchmakingInterfaceBeamable, ESPMode::ThreadSafe> FMatchmakingInterfacePtr;
typedef TSharedPtr<class FOnlineStatsBeamable, ESPMode::ThreadSafe> FOnlineStatsBeamablePtr;

class FUserOnlineAccountBeamable;

class ONLINESUBSYSTEMBEAMABLE_API FOnlineSubsystemBeamable : public FOnlineSubsystemImpl
{
public:
	// IOnlineSubsystem
	virtual IOnlineIdentityPtr GetIdentityInterface() const override;
	virtual IOnlineSessionPtr GetSessionInterface() const override;
	virtual IOnlineFriendsPtr GetFriendsInterface() const override;
	virtual IOnlinePartyPtr GetPartyInterface() const override;
	virtual IOnlineStatsPtr GetStatsInterface() const override;

	virtual bool IsLocalPlayer(const FUniqueNetId& UniqueId) const override;
	virtual bool Init() override;
	virtual bool Shutdown() override;
	virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual bool IsEnabled() const override;
	virtual FString GetAppId() const override;
	virtual FText GetOnlineServiceName() const override;


	/** Only the factory makes instances */
	FOnlineSubsystemBeamable() = delete;

	FOnlineSubsystemBeamable(FName InInstanceName) : FOnlineSubsystemImpl(BEAMABLE_SUBSYSTEM, InInstanceName)
	{
		GetBuildUniqueId();
	}

	/**
	 * Gets the game instance associated with this Subsystem. 
	 */
	UGameInstance* GetGameInstance();

	/**
	 * Short-hand for getting the Request Tracker engine subsystem. 
	 */
	UBeamRequestTracker* GetRequestTracker();

	/**
	 * Short-hand for getting the UserSlots engine subsystem. 
	 */
	UBeamUserSlots* GetUserSlots();

	/**
	 * Short-hand for getting the net id ptr for a local slot. 
	 */
	FUniqueNetIdPtr GetUniqueIdForSlot(FUserSlot Slot) const;

	/**
	 * Short-hand for getting the account ptr for a local slot. 
	 */
	TSharedPtr<FUserOnlineAccountBeamable> GetAccountForSlot(FUserSlot Slot) const;

	/**
	 * Short-hand for getting the account ptr for a local id. 
	 */
	TSharedPtr<FUserOnlineAccountBeamable> GetAccountForId(const FUniqueNetId& Id) const;

	FOnlineStatsBeamablePtr GetStatsInterfacePtr() const { return StatsInterface; }
protected:
	FOnlineSessionBeamablePtr SessionInterface;
	FOnlineIdentityBeamablePtr IdentityInterface;
	FOnlineStatsBeamablePtr StatsInterface;
};

typedef TSharedPtr<FOnlineSubsystemBeamable, ESPMode::ThreadSafe> FOnlineSubsystemBeamablePtr;
