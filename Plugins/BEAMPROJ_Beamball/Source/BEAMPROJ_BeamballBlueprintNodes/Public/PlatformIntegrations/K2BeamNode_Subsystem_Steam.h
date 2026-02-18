#pragma once
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BEAMPROJ_Beamball/Public/PlatformIntegrations/BeamableSteam.h"


#include "K2BeamNode_Subsystem_Steam.generated.h"


//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetHathoraPings"

UCLASS

(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetSteamData : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamableSteam - TryGetSteamData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableSteam, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableSteam, TryGetSteamData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableSteam::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
