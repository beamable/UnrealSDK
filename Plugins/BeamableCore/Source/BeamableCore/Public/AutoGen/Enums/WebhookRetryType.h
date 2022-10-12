
#pragma once

#include "CoreMinimal.h"

#include "WebhookRetryType.generated.h"

UENUM(BlueprintType)
enum class EWebhookRetryType : uint8
{
	None UMETA(DisplayName="None", SerializationName="None"),
	Once UMETA(DisplayName="Once", SerializationName="Once"),
	ExponentialBackoff UMETA(DisplayName="Exponential Backoff", SerializationName="ExponentialBackoff")		
};

UCLASS(BlueprintType)
class UWebhookRetryTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "WebhookRetryType To Serialization Name", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static FString WebhookRetryTypeToSerializationName(EWebhookRetryType Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookRetryType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To WebhookRetryType", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static EWebhookRetryType SerializationNameToWebhookRetryType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookRetryType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);
			if(Value == SerializationName)
				return static_cast<EWebhookRetryType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EWebhookRetryType();
	}	
};

