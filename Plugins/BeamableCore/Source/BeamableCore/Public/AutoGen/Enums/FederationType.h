#pragma once

#include "CoreMinimal.h"

#include "FederationType.generated.h"

UENUM(BlueprintType, Category="Beam|Shared|Enums")
enum class EFederationType : uint8
{
	BEAM_IFederatedPlayerInit UMETA(DisplayName="I Federated Player Init"),
	BEAM_IFederatedInventory UMETA(DisplayName="I Federated Inventory"),
	BEAM_IFederatedLogin UMETA(DisplayName="I Federated Login"),
	BEAM_IFederatedGameServer UMETA(DisplayName="I Federated Game Server"),
	BEAM_IFederatedCommerce UMETA(DisplayName="I Federated Commerce")		
};

UCLASS(BlueprintType, Category="Beam|Shared|Enums")
class BEAMABLECORE_API UFederationTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "FederationType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Shared|Enums")
	static FString FederationTypeToSerializationName(EFederationType Value)
	{
		const UEnum* Enum = StaticEnum<EFederationType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To FederationType", CompactNodeTitle = "->"), Category="Beam|Shared|Enums")
	static EFederationType SerializationNameToFederationType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EFederationType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EFederationType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EFederationType();
	}	
};

