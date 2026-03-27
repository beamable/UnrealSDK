#pragma once
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BEAMPROJ_Beamball/Public/PlatformIntegrations/BeamableEdgegap.h"


#include "K2BeamNode_Subsystem_Edgegap.generated.h"

/***
 *      ______                          _         
 *     |  ____|                        | |        
 *     | |__    __   __   ___   _ __   | |_   ___ 
 *     |  __|   \ \ / /  / _ \ | '_ \  | __| / __|
 *     | |____   \ V /  |  __/ | | | | | |_  \__ \
 *     |______|   \_/    \___| |_| |_|  \__| |___/
 *                                                
 *                                                
 */

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_RefreshPings"

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
