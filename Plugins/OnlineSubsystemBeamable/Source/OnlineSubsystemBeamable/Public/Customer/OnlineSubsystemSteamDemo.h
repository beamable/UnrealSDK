#pragma once

#ifdef BEAM_ENABLE_BEAMABLE_OSS

#include "Beamable/OnlineIdentityBeamable.h"
#include "Beamable/OnlineSessionInterfaceBeamable.h"
#include "Beamable/OnlineSubsystemBeamable.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"

class FOnlineSubsystemSteamDemo final : public FOnlineSubsystemBeamable
{
public:
	FOnlineSubsystemSteamDemo() = delete;

	explicit FOnlineSubsystemSteamDemo(const FName& InInstanceName)
		: FOnlineSubsystemBeamable(InInstanceName)
	{
	}

	virtual bool Init() override
	{
		const bool bDidRunCorrectly = FOnlineSubsystemBeamable::Init();

		return true;
	}
};

#endif
