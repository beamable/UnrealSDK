#pragma once

#include "CoreMinimal.h"

#include "ContentVisibility.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EContentVisibility : uint8
{
	BEAM_public UMETA(DisplayName="Public"),
	BEAM_private UMETA(DisplayName="Private")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UContentVisibilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - ContentVisibility To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString ContentVisibilityToSerializationName(EContentVisibility Value)
	{
		const UEnum* Enum = StaticEnum<EContentVisibility>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To ContentVisibility", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EContentVisibility SerializationNameToContentVisibility(FString Value)
	{
		const UEnum* Enum = StaticEnum<EContentVisibility>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EContentVisibility>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EContentVisibility();
	}	
};

