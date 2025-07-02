#pragma once
#include "BeamPIE_LobbySettings.h"
#include "BeamPIE_UserSlotHandle.h"

#include "BeamPIE_Settings.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPIE_Settings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid SettingsId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FBeamPIE_UserSlotHandle, FBeamGamerTag> AssignedUsers;

	// Lobby
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamPIE_LobbySettings FakeLobby;
};
