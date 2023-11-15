#pragma once

#include "CoreMinimal.h"

#include "LobbyRestriction.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class ELobbyRestriction : uint8
{
	BEAM_Closed UMETA(DisplayName="Closed"),
	BEAM_Open UMETA(DisplayName="Open")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API ULobbyRestrictionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - LobbyRestriction To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString LobbyRestrictionToSerializationName(ELobbyRestriction Value)
	{
		const UEnum* Enum = StaticEnum<ELobbyRestriction>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To LobbyRestriction", CompactNodeTitle = "->"), Category="Beam|Enums")
	static ELobbyRestriction SerializationNameToLobbyRestriction(FString Value)
	{
		const UEnum* Enum = StaticEnum<ELobbyRestriction>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<ELobbyRestriction>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return ELobbyRestriction();
	}	
};

