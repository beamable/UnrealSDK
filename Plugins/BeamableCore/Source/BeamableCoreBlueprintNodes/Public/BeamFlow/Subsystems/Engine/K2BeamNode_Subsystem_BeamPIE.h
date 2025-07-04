#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/PIE/BeamPIE.h"

#include "K2BeamNode_Subsystem_BeamPIE.generated.h"


//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BeamInitPIE"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BeamInitPIE : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - PIE - Init SDK"); }

	virtual FText GetKeywords() const override { return FText::FromString(Super::GetKeywords().ToString() + " PIE"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, BeamInitPIEOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPIE::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BeamPreparePIE"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BeamPreparePIE : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - PIE - Prepare State"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, BeamPreparePIEOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPIE::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
