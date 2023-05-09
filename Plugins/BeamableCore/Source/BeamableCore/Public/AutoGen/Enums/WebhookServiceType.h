#pragma once

#include "CoreMinimal.h"

#include "WebhookServiceType.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EWebhookServiceType : uint8
{
	BEAM_UserMicroservice UMETA(DisplayName="User Microservice"),
	BEAM_ObjectService UMETA(DisplayName="Object Service"),
	BEAM_BasicService UMETA(DisplayName="Basic Service")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UWebhookServiceTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - WebhookServiceType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString WebhookServiceTypeToSerializationName(EWebhookServiceType Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookServiceType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To WebhookServiceType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EWebhookServiceType SerializationNameToWebhookServiceType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookServiceType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EWebhookServiceType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EWebhookServiceType();
	}	
};

