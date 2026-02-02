#pragma once
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"

#include "FBeamPIE_PerUserSetting.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPIE_PlayerPartySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPartyLeader = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PartyId = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> PartyTags = {};
};

USTRUCT(BlueprintType)
struct FBeamPIE_PerUserSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag GamerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> LobbyData = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamPIE_PlayerPartySettings PartySettings = {};
};
