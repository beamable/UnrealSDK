
#include "BeamableCore/Public/AutoGen/WebhookRewardLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UWebhookRewardLibrary::WebhookRewardToJsonString(const UWebhookReward* Serializable, const bool Pretty)
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

UWebhookReward* UWebhookRewardLibrary::Make(UWebhookInvocationStrategy* Strategy, FOptionalString WebhookSymbol, FOptionalWebhookComet WebHookComet, UObject* Outer)
{
	auto Serializable = NewObject<UWebhookReward>(Outer);
	Serializable->Strategy = Strategy;
	Serializable->WebhookSymbol = WebhookSymbol;
	Serializable->WebHookComet = WebHookComet;
	
	return Serializable;
}

void UWebhookRewardLibrary::Break(const UWebhookReward* Serializable, UWebhookInvocationStrategy*& Strategy, FOptionalString& WebhookSymbol, FOptionalWebhookComet& WebHookComet)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Strategy = Serializable->Strategy;
		WebhookSymbol = Serializable->WebhookSymbol;
		WebHookComet = Serializable->WebHookComet;
	}
		
}

