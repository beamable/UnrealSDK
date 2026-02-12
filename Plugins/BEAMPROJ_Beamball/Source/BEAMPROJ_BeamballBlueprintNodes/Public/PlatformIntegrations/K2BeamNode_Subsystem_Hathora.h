#pragma once
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BEAMPROJ_Beamball/Public/BeamableHathora.h"


#include "K2BeamNode_Subsystem_Hathora.generated.h"

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
class UK2BeamNode_Operation_RefreshPings : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "BeamableHathora - Operation - RefreshPings"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableHathora, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableHathora, RefreshPingsOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableHathora::StaticClass(); }

	virtual bool IsNodeSafeToIgnore() const override { return false; }
};

#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetHathoraPings"

UCLASS

(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetHathoraPings : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamableHathora - TryGetHathoraPings"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableHathora, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableHathora, TryGetHathoraPings); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableHathora::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
