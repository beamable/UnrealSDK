#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Runtime/BeamRuntime.h"

#include "K2BeamNode_Operation_Auth.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FrictionlessAuth"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FrictionlessAuth : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Frictionless Authentication"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginFrictionlessOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }	
};

#undef LOCTEXT_NAMESPACE
