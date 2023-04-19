
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategyLibrary.h"

#include "CoreMinimal.h"


FString UWebhookInvocationStrategyLibrary::WebhookInvocationStrategyToJsonString(const UWebhookInvocationStrategy* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UWebhookInvocationStrategy* UWebhookInvocationStrategyLibrary::Make(EWebhookInvocationType InvocationType, EWebhookRetryType RetryType, UObject* Outer)
{
	auto Serializable = NewObject<UWebhookInvocationStrategy>(Outer);
	Serializable->InvocationType = InvocationType;
	Serializable->RetryType = RetryType;
	
	return Serializable;
}

void UWebhookInvocationStrategyLibrary::Break(const UWebhookInvocationStrategy* Serializable, EWebhookInvocationType& InvocationType, EWebhookRetryType& RetryType)
{
	InvocationType = Serializable->InvocationType;
	RetryType = Serializable->RetryType;
		
}

