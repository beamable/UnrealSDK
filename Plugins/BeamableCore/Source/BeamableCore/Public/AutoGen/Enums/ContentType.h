#pragma once

#include "CoreMinimal.h"

#include "ContentType.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EContentType : uint8
{
	BEAM_content UMETA(DisplayName="Content"),
	BEAM_text UMETA(DisplayName="Text"),
	BEAM_binary UMETA(DisplayName="Binary")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UContentTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - ContentType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString ContentTypeToSerializationName(EContentType Value)
	{
		const UEnum* Enum = StaticEnum<EContentType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To ContentType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EContentType SerializationNameToContentType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EContentType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EContentType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EContentType();
	}	
};

