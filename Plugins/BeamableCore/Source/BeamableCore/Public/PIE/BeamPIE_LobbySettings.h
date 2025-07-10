#pragma once
#include "BeamPIE_LobbyPlayerSettings.h"
#include "BeamPIE_UserSlotHandle.h"
#include "AutoGen/Enums/BeamLobbyRestriction.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"

#include "BeamPIE_LobbySettings.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPIE_LobbySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldAutoCreateLobby = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby", EditConditionHides))
	bool bIsDedicatedServer = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby && bIsDedicatedServer", EditConditionHides, AllowedClasses="/Script/Engine.World"))
	TSoftObjectPtr<UWorld> ServerStartMapOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby", EditConditionHides, BeamContentTypeFilter="game_types", BeamContentTypeFilterMode="tree"))
	FBeamContentId GameType = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby && !bIsDedicatedServer", EditConditionHides))
	FBeamPIE_UserSlotHandle HostPlayer = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby && !bIsDedicatedServer", EditConditionHides))
	EBeamLobbyRestriction LobbyType = EBeamLobbyRestriction::BEAM_Null;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby", EditConditionHides))
	TMap<FString, FString> LobbyGlobalData = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateLobby", EditConditionHides))
	TMap<FBeamPIE_UserSlotHandle, FBeamPIE_LobbyPlayerSettings> PerPlayerSettings = {};
};
