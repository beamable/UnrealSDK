#pragma once
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BEAMPROJ_Beamball/Public/PlatformIntegrations/BeamableEdgegap.h"


#include "K2BeamNode_Subsystem_Edgegap.generated.h"



//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     


#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_UpdateEdgegapGeolocation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UpdateEdgegapGeolocation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beamable Edgegap - Operation - Update Geolocation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEdgegap, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEdgegap, UpdateGeolocationStatOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableEdgegap::StaticClass(); }

	virtual bool IsNodeSafeToIgnore() const override { return false; }
};

#undef LOCTEXT_NAMESPACE
