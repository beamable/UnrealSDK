#pragma once
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamBackend/ReplacementTypes/BeamTag.h"

#include "FBeamPIE_PerUserSetting.generated.h"

USTRUCT(BlueprintType)
struct FBeamPIE_PerUserSetting
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag GamerTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> LobbyData  = {};
};