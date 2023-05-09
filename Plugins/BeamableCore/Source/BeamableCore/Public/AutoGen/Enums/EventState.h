#pragma once

#include "CoreMinimal.h"

#include "EventState.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EEventState : uint8
{
	BEAM_running UMETA(DisplayName="Running"),
	BEAM_unknown UMETA(DisplayName="Unknown"),
	BEAM_cancelled UMETA(DisplayName="Cancelled"),
	BEAM_done UMETA(DisplayName="Done"),
	BEAM_pending UMETA(DisplayName="Pending")		
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
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To EventState", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EEventState SerializationNameToEventState(FString Value)
	{
		const UEnum* Enum = StaticEnum<EEventState>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EEventState>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EEventState();
	}	
};

