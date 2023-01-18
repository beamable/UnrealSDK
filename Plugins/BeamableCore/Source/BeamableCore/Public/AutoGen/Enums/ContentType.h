
#pragma once

#include "CoreMinimal.h"

#include "ContentType.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EContentType : uint8
{
	content UMETA(DisplayName="Content"),
	text UMETA(DisplayName="Text"),
	binary UMETA(DisplayName="Binary")		
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
		const FString SerializationName = Enum->GetNameStringByValue(NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To ContentType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EContentType SerializationNameToContentType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EContentType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetNameStringByValue(NameIndex);
			if(Value == SerializationName)
				return static_cast<EContentType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EContentType();
	}	
};

