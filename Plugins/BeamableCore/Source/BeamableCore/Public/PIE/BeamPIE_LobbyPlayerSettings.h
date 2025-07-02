#pragma once
#include "BeamBackend/ReplacementTypes/BeamTag.h"
#include "BeamPIE_LobbyPlayerSettings.generated.h"
USTRUCT(BlueprintType)
struct FBeamPIE_LobbyPlayerSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamTag> Tags = {};
};
