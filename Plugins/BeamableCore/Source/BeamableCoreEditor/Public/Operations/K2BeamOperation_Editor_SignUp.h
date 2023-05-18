#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/BeamEditor.h"

#include "K2BeamOperation_Editor_SignUp.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamOperation_Editor_SignUp"

UCLASS(meta=(BeamFlowNode))
class UK2BeamOperation_Editor_SignUp : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Editor Operation - Sign Up"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamEditor, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamEditor, SignUpOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamEditor::StaticClass(); }

};

#undef LOCTEXT_NAMESPACE
