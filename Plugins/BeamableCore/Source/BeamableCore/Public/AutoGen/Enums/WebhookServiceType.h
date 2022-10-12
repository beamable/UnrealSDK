
#pragma once

#include "CoreMinimal.h"

#include "WebhookServiceType.generated.h"

UENUM(BlueprintType)
enum class EWebhookServiceType : uint8
{
	UserMicroservice UMETA(DisplayName="User Microservice", SerializationName="UserMicroservice"),
	ObjectService UMETA(DisplayName="Object Service", SerializationName="ObjectService"),
	BasicService UMETA(DisplayName="Basic Service", SerializationName="BasicService")		
};

UCLASS(BlueprintType)
class UWebhookServiceTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "WebhookServiceType To Serialization Name", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static FString WebhookServiceTypeToSerializationName(EWebhookServiceType Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookServiceType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To WebhookServiceType", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static EWebhookServiceType SerializationNameToWebhookServiceType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookServiceType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);
			if(Value == SerializationName)
				return static_cast<EWebhookServiceType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EWebhookServiceType();
	}	
};
