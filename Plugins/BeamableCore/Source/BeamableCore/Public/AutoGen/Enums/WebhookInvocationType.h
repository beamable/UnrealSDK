
#pragma once

#include "CoreMinimal.h"

#include "WebhookInvocationType.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EWebhookInvocationType : uint8
{
	NonBlocking UMETA(DisplayName="Non Blocking"),
	Blocking UMETA(DisplayName="Blocking")		
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UWebhookInvocationTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - WebhookInvocationType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString WebhookInvocationTypeToSerializationName(EWebhookInvocationType Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookInvocationType>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByValue(NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Beam - Serialization Name To WebhookInvocationType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EWebhookInvocationType SerializationNameToWebhookInvocationType(FString Value)
	{
		const UEnum* Enum = StaticEnum<EWebhookInvocationType>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetNameStringByValue(NameIndex);
			if(Value == SerializationName)
				return static_cast<EWebhookInvocationType>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EWebhookInvocationType();
	}	
};

