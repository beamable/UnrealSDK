#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Content/BeamContentSubsystem.h"

#include "K2BeamNode_Operation_Content.generated.h"


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchContentManifest"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchContentManifest : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Content - FetchContentManifest"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, FetchContentManifestOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamContentSubsystem::StaticClass(); }

	virtual UEnum* GetOperationSubTypeEnum() const override { return StaticEnum<EDefaultOperationEventSubType>(); }

	virtual TMap<uint8, UScriptStruct*> GetOperationSubTypeUStructs() const override
	{
		TMap<uint8, UScriptStruct*> SubEventToDataType;
		SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
		return SubEventToDataType;
	}

	virtual TMap<uint8, UClass*> GetOperationSubTypeConversionFunctionClass() const override
	{
		TMap<uint8, UClass*> SubEventToConversionClass;
		SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
		return SubEventToConversionClass;
	}

	virtual TMap<uint8, FName> GetOperationSubTypeConversionFunctionName() const override
	{
		// Use this macro to point to the conversion function and map it to the sub-event type.
		// GET_FUNCTION_NAME_CHECKED_OneParam(USubTypeConversionFunctionClass, ConversionFunction, FString))	
		TMap<uint8, FName> SubEventToConversionClass;
		SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), TEXT(""));
		return SubEventToConversionClass;
	}
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchIndividualContentBatch"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchIndividualContentBatch : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Content - Fetch Individual Content (Batch)"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, FetchIndividualContentBatchOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamContentSubsystem::StaticClass(); }

	virtual UEnum* GetOperationSubTypeEnum() const override { return StaticEnum<EDefaultOperationEventSubType>(); }

	virtual TMap<uint8, UScriptStruct*> GetOperationSubTypeUStructs() const override
	{
		TMap<uint8, UScriptStruct*> SubEventToDataType;
		SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
		return SubEventToDataType;
	}

	virtual TMap<uint8, UClass*> GetOperationSubTypeConversionFunctionClass() const override
	{
		TMap<uint8, UClass*> SubEventToConversionClass;
		SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
		return SubEventToConversionClass;
	}

	virtual TMap<uint8, FName> GetOperationSubTypeConversionFunctionName() const override
	{
		// Use this macro to point to the conversion function and map it to the sub-event type.
		// GET_FUNCTION_NAME_CHECKED_OneParam(USubTypeConversionFunctionClass, ConversionFunction, FString))	
		TMap<uint8, FName> SubEventToConversionClass;
		SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), TEXT(""));
		return SubEventToConversionClass;
	}
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchIndividualContent"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchIndividualContent : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Content - Fetch Individual Content"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamContentSubsystem, FetchIndividualContentOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamContentSubsystem::StaticClass(); }

	virtual UEnum* GetOperationSubTypeEnum() const override { return StaticEnum<EDefaultOperationEventSubType>(); }

	virtual TMap<uint8, UScriptStruct*> GetOperationSubTypeUStructs() const override
	{
		TMap<uint8, UScriptStruct*> SubEventToDataType;
		SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
		return SubEventToDataType;
	}

	virtual TMap<uint8, UClass*> GetOperationSubTypeConversionFunctionClass() const override
	{
		TMap<uint8, UClass*> SubEventToConversionClass;
		SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
		return SubEventToConversionClass;
	}

	virtual TMap<uint8, FName> GetOperationSubTypeConversionFunctionName() const override
	{
		// Use this macro to point to the conversion function and map it to the sub-event type.
		// GET_FUNCTION_NAME_CHECKED_OneParam(USubTypeConversionFunctionClass, ConversionFunction, FString))	
		TMap<uint8, FName> SubEventToConversionClass;
		SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), TEXT(""));
		return SubEventToConversionClass;
	}
};

#undef LOCTEXT_NAMESPACE
