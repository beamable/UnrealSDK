#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/BeamEditor.h"

#include "K2BeamOperation_Editor_SelectRealm.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamOperation_Editor_SelectRealm"

UCLASS(meta=(BeamFlowNode))
class UK2BeamOperation_Editor_SelectRealm : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Editor Operation - Select Realm"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamEditor, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamEditor, SelectRealmOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamEditor::StaticClass(); }

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
