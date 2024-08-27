#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Microservices/BeamMicroservicesEditor.h"
#include "K2BeamOperation_Editor_Microservices.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamOperation_Editor_Microservices_Update"

UCLASS(meta=(BeamFlowNode))
class UK2BeamOperation_Editor_Microservices_Run : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Editor Operation - Microservices - Run");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamMicroservicesEditor, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamMicroservicesEditor, RunLocalMicroservicesOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMicroservicesEditor::StaticClass(); }	
};

UCLASS(meta=(BeamFlowNode))
class UK2BeamOperation_Editor_Microservices_Deploy : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Editor Operation - Microservices - Deploy");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamMicroservicesEditor, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamMicroservicesEditor, DeployRemoteMicroservicesOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMicroservicesEditor::StaticClass(); }	
};

UCLASS(meta=(BeamFlowNode))
class UK2BeamOperation_Editor_Microservices_Stop : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Editor Operation - Microservices - Stop");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamMicroservicesEditor, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamMicroservicesEditor, StopLocalMicroservicesOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMicroservicesEditor::StaticClass(); }	
};

#undef LOCTEXT_NAMESPACE
