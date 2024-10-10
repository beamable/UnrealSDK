#include "Beamable/OnlineSubsystemBeamable.h"
#include "Beamable/OnlineIdentityBeamable.h"
#include "Beamable/OnlineStatsBeamable.h"
#include "Beamable/OnlineSessionInterfaceBeamable.h"

// implement all the other IOnlineSubsystem functions

IOnlineIdentityPtr FOnlineSubsystemBeamable::GetIdentityInterface() const
{
	return IdentityInterface;
}

IOnlineSessionPtr FOnlineSubsystemBeamable::GetSessionInterface() const
{
	return SessionInterface;
}

IOnlineStatsPtr FOnlineSubsystemBeamable::GetStatsInterface() const
{
	return StatsInterface;
}

IOnlineFriendsPtr FOnlineSubsystemBeamable::GetFriendsInterface() const
{
	return nullptr;
}

IOnlinePartyPtr FOnlineSubsystemBeamable::GetPartyInterface() const
{
	return nullptr;
}


bool FOnlineSubsystemBeamable::IsLocalPlayer(const FUniqueNetId& UniqueId) const
{
	return FOnlineSubsystemImpl::IsLocalPlayer(UniqueId);
}

bool FOnlineSubsystemBeamable::Init()
{
	const bool bPragmaInit = true;

	if (bPragmaInit)
	{
		IdentityInterface = MakeShareable(new FOnlineIdentityBeamable(this));
		SessionInterface = MakeShareable(new FOnlineSessionBeamable(this));
		StatsInterface = MakeShareable(new FOnlineStatsBeamable(this));
	}

	return bPragmaInit;
}

bool FOnlineSubsystemBeamable::Shutdown()
{
	return FOnlineSubsystemImpl::Shutdown();
}

bool FOnlineSubsystemBeamable::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return FOnlineSubsystemImpl::Exec(InWorld, Cmd, Ar);
}

bool FOnlineSubsystemBeamable::IsEnabled() const
{
	return FOnlineSubsystemImpl::IsEnabled();
}

FString FOnlineSubsystemBeamable::GetAppId() const
{
	return TEXT("Beamable");
}

FText FOnlineSubsystemBeamable::GetOnlineServiceName() const
{
	return NSLOCTEXT("OnlineSubsystemPragma", "OnlineServiceName", "Beamable");
}

UGameInstance* FOnlineSubsystemBeamable::GetGameInstance()
{
	const auto Name = OSS_BEAMABLE_GAME_INSTANCE();
	return Cast<UGameInstance>(GetNamedInterface(*Name));
}

UBeamRequestTracker* FOnlineSubsystemBeamable::GetRequestTracker()
{
	return GEngine->GetEngineSubsystem<UBeamRequestTracker>();
}

UBeamUserSlots* FOnlineSubsystemBeamable::GetUserSlots()
{
	return GEngine->GetEngineSubsystem<UBeamUserSlots>();
}

FUniqueNetIdPtr FOnlineSubsystemBeamable::GetUniqueIdForSlot(FUserSlot Slot) const
{
	return IdentityInterface->GetBeamableUser(Slot);
}

TSharedPtr<FUserOnlineAccountBeamable> FOnlineSubsystemBeamable::GetAccountForSlot(FUserSlot Slot) const
{
	if (IdentityInterface->GetBeamableUser(Slot).IsValid())
		return IdentityInterface->GetUserAccountBeamable(*IdentityInterface->GetBeamableUser(Slot));
	return nullptr;
}

TSharedPtr<FUserOnlineAccountBeamable> FOnlineSubsystemBeamable::GetAccountForId(const FUniqueNetId& Id) const
{
	const auto Account = IdentityInterface->GetUserAccount(Id);
	if (Account)
	{
		const auto Ref = Account->GetUserId();
		if (IdentityInterface->GetBeamableUsers().Contains(Ref))
			return IdentityInterface->GetBeamableUsers()[Ref];
	}

	return nullptr;
}
