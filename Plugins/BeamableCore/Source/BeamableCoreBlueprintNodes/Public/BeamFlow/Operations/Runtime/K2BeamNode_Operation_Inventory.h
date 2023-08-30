#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"

#include "K2BeamNode_Operation_Inventory.generated.h"


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitInventoryUpdate"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CommitInventoryUpdate : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Inventory - CommitInventoryUpdate"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, CommitInventoryUpdateOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }

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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ModifyCurrencies"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_ModifyCurrencies : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Inventory - ModifyCurrencies"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, ModifyCurrenciesOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }

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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ModifyCurrencies"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchAllInventory : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Inventory - FetchAllInventory"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, FetchAllInventoryOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }

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
