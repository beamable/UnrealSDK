#pragma once

#include "CoreMinimal.h"

#include "PresenceStatus.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EPresenceStatus : uint8
{
	BEAM_Visible UMETA(DisplayName="Visible"),
	BEAM_Invisible UMETA(DisplayName="Invisible"),
	BEAM_Dnd UMETA(DisplayName="Dnd"),
	BEAM_Away UMETA(DisplayName="Away")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UPresenceStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - PresenceStatus To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString PresenceStatusToSerializationName(EPresenceStatus Value)
	{
		const UEnum* Enum = StaticEnum<EPresenceStatus>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To PresenceStatus", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EPresenceStatus SerializationNameToPresenceStatus(FString Value)
	{
		const UEnum* Enum = StaticEnum<EPresenceStatus>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EPresenceStatus>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EPresenceStatus();
	}	
};

