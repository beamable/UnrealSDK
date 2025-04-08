#pragma once

#include "CoreMinimal.h"

#include "FriendSource.generated.h"

UENUM(BlueprintType, Category="Beam|Shared|Enums")
enum class EFriendSource : uint8
{
	BEAM_native UMETA(DisplayName="Native"),
	BEAM_facebook UMETA(DisplayName="Facebook")		
};

UCLASS(BlueprintType, Category="Beam|Shared|Enums")
class BEAMABLECORE_API UFriendSourceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "FriendSource To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Shared|Enums")
	static FString FriendSourceToSerializationName(EFriendSource Value)
	{
		const UEnum* Enum = StaticEnum<EFriendSource>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To FriendSource", CompactNodeTitle = "->"), Category="Beam|Shared|Enums")
	static EFriendSource SerializationNameToFriendSource(FString Value)
	{
		const UEnum* Enum = StaticEnum<EFriendSource>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EFriendSource>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EFriendSource();
	}	
};

