
#pragma once

#include "CoreMinimal.h"

#include "GroupType.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EGroupType : uint8
{
	guild UMETA(DisplayName="Guild"),
	subgroup UMETA(DisplayName="Subgroup")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UGroupTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - GroupType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString GroupTypeToSerializationName(EGroupType Value)
	{
		const UEnum* Enum = StaticEnum<EGroupType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByValue(NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To GroupType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EGroupType SerializationNameToGroupType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EGroupType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetNameStringByValue(NameIndex);
			if(Value == SerializationName)
				return static_cast<EGroupType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EGroupType();
	}	
};

