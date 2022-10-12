
#pragma once

#include "CoreMinimal.h"

#include "EventState.generated.h"

UENUM(BlueprintType)
enum class EEventState : uint8
{
	Running UMETA(DisplayName="Running", SerializationName="running"),
	Unknown UMETA(DisplayName="Unknown", SerializationName="unknown"),
	Cancelled UMETA(DisplayName="Cancelled", SerializationName="cancelled"),
	Done UMETA(DisplayName="Done", SerializationName="done"),
	Pending UMETA(DisplayName="Pending", SerializationName="pending")		
};

UCLASS(BlueprintType)
class UEventStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "EventState To Serialization Name", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static FString EventStateToSerializationName(EEventState Value)
	{
		const UEnum* Enum = StaticEnum<EEventState>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To EventState", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static EEventState SerializationNameToEventState(FString Value)
	{
		const UEnum* Enum = StaticEnum<EEventState>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);
			if(Value == SerializationName)
				return static_cast<EEventState>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EEventState();
	}	
};

