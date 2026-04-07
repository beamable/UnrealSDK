#pragma once
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BEAMPROJ_Beamball/Public/PlatformIntegrations/BeamableEOS.h"


#include "K2BeamNode_Subsystem_EOS.generated.h"


//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LoginWithEOS"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LoginWithEOS : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beamable EOS - Operation - Login With EOS"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEOS, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEOS, LoginWithEOSOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableEOS::StaticClass(); }

	virtual bool IsNodeSafeToIgnore() const override { return false; }
};

#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetEOSDataByLocalPlayerIndex"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetEOSDataByLocalPlayerIndex : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamableEOS - TryGetEOSDataByLocalPlayerIndex"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEOS, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEOS, TryGetEOSDataByLocalPlayerIndex); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableEOS::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetEOSDataForSlot"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetEOSDataForSlot : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamableEOS - TryGetEOSDataForSlot"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEOS, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableEOS, TryGetEOSDataForSlot); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableEOS::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
