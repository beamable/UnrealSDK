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

	// TODO: I should read this from ULevelEditorPlaySettings::PlayAsClient/PlayAsStandalone vs "PlayAsListenServer".
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDedicatedServer = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BeamContentTypeFilter="game_types", BeamContentTypeFilterMode="tree"))
	FBeamContentId GameType = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!bIsDedicatedServer"))
	FBeamPIE_UserSlotHandle HostPlayer = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!bIsDedicatedServer"))
	EBeamLobbyRestriction LobbyType = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> LobbyGlobalData = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FBeamPIE_UserSlotHandle, FBeamPIE_LobbyPlayerSettings> PerPlayerSettings = {};
};
