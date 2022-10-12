
#pragma once

#include "CoreMinimal.h"

#include "GroupType.generated.h"

UENUM(BlueprintType)
enum class EGroupType : uint8
{
	Guild UMETA(DisplayName="Guild", SerializationName="guild"),
	Subgroup UMETA(DisplayName="Subgroup", SerializationName="subgroup")		
};

UCLASS(BlueprintType)
class UGroupTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GroupType To Serialization Name", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static FString GroupTypeToSerializationName(EGroupType Value)
	{
		const UEnum* Enum = StaticEnum<EGroupType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To GroupType", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static EGroupType SerializationNameToGroupType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EGroupType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);
			if(Value == SerializationName)
				return static_cast<EGroupType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EGroupType();
	}	
};

