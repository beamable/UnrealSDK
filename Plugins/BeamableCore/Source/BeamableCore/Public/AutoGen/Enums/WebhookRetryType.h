#pragma once

#include "CoreMinimal.h"

#include "WebhookRetryType.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EWebhookRetryType : uint8
{
	BEAM_None UMETA(DisplayName="None"),
	BEAM_Once UMETA(DisplayName="Once"),
	BEAM_ExponentialBackoff UMETA(DisplayName="Exponential Backoff")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UWebhookRetryTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - WebhookRetryType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString WebhookRetryTypeToSerializationName(EWebhookRetryType Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookRetryType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To WebhookRetryType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EWebhookRetryType SerializationNameToWebhookRetryType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookRetryType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if(Value == SerializationName)
				return static_cast<EWebhookRetryType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EWebhookRetryType();
	}	
};

