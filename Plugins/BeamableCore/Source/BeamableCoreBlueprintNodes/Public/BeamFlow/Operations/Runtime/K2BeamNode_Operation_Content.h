#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Content/BeamContentSubsystem.h"

#include "K2BeamNode_Operation_Content.generated.h"


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchContentManifest"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchContentManifest : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Content - FetchContentManifest"); }

	virtual FString GetServiceName() const override { return FString("Content"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, FetchContentManifestOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamContentSubsystem::StaticClass(); }	
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchIndividualContentBatch"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchIndividualContentBatch : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Content - Fetch Individual Content (Batch)"); }

	virtual FString GetServiceName() const override { return FString("Content"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, FetchIndividualContentBatchOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamContentSubsystem::StaticClass(); }	
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchIndividualContent"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchIndividualContent : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Content - Fetch Individual Content"); }

	virtual FString GetServiceName() const override { return FString("Content"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, FetchIndividualContentOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamContentSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
