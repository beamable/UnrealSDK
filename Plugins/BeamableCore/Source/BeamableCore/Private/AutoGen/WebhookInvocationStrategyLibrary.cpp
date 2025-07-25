
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UWebhookInvocationStrategyLibrary::WebhookInvocationStrategyToJsonString(const UWebhookInvocationStrategy* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UWebhookInvocationStrategy* UWebhookInvocationStrategyLibrary::Make(EBeamWebhookInvocationType InvocationType, EBeamWebhookRetryType RetryType, UObject* Outer)
{
	auto Serializable = NewObject<UWebhookInvocationStrategy>(Outer);
	Serializable->InvocationType = InvocationType;
	Serializable->RetryType = RetryType;
	
	return Serializable;
}

void UWebhookInvocationStrategyLibrary::Break(const UWebhookInvocationStrategy* Serializable, EBeamWebhookInvocationType& InvocationType, EBeamWebhookRetryType& RetryType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		InvocationType = Serializable->InvocationType;
		RetryType = Serializable->RetryType;
	}
		
}

