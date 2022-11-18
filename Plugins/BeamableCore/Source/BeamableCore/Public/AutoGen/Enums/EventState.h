
#pragma once

#include "CoreMinimal.h"

#include "EventState.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EEventState : uint8
{
	running UMETA(DisplayName="Running"),
	unknown UMETA(DisplayName="Unknown"),
	cancelled UMETA(DisplayName="Cancelled"),
	done UMETA(DisplayName="Done"),
	pending UMETA(DisplayName="Pending")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UEventStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - EventState To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString EventStateToSerializationName(EEventState Value)
	{
		const UEnum* Enum = StaticEnum<EEventState>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByValue(NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To EventState", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EEventState SerializationNameToEventState(FString Value)
	{
		const UEnum* Enum = StaticEnum<EEventState>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetNameStringByValue(NameIndex);
			if(Value == SerializationName)
				return static_cast<EEventState>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EEventState();
	}	
};

