
#pragma once

#include "CoreMinimal.h"

#include "WebhookInvocationType.generated.h"

UENUM(BlueprintType)
enum class EWebhookInvocationType : uint8
{
	NonBlocking UMETA(DisplayName="Non Blocking", SerializationName="NonBlocking"),
	Blocking UMETA(DisplayName="Blocking", SerializationName="Blocking")		
};

UCLASS(BlueprintType)
class UWebhookInvocationTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "WebhookInvocationType To Serialization Name", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static FString WebhookInvocationTypeToSerializationName(EWebhookInvocationType Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookInvocationType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To WebhookInvocationType", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static EWebhookInvocationType SerializationNameToWebhookInvocationType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookInvocationType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);
			if(Value == SerializationName)
				return static_cast<EWebhookInvocationType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EWebhookInvocationType();
	}	
};

