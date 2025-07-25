
#include "BeamableCore/Public/AutoGen/PlayerRewardLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerRewardLibrary::PlayerRewardToJsonString(const UPlayerReward* Serializable, const bool Pretty)
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

UPlayerReward* UPlayerRewardLibrary::Make(TArray<UItemCreateRequestBody*> AddItemRequests, TMap<FString, FString> AddCurrencyMap, FOptionalBool bApplyVipBonus, FOptionalString Description, FOptionalArrayOfCurrencyChangeReward ChangeCurrencies, FOptionalArrayOfWebhookReward CallWebhooks, FOptionalArrayOfNewItemReward AddItems, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerReward>(Outer);
	Serializable->AddItemRequests = AddItemRequests;
	Serializable->AddCurrencyMap = AddCurrencyMap;
	Serializable->bApplyVipBonus = bApplyVipBonus;
	Serializable->Description = Description;
	Serializable->ChangeCurrencies = ChangeCurrencies;
	Serializable->CallWebhooks = CallWebhooks;
	Serializable->AddItems = AddItems;
	
	return Serializable;
}

void UPlayerRewardLibrary::Break(const UPlayerReward* Serializable, TArray<UItemCreateRequestBody*>& AddItemRequests, TMap<FString, FString>& AddCurrencyMap, FOptionalBool& bApplyVipBonus, FOptionalString& Description, FOptionalArrayOfCurrencyChangeReward& ChangeCurrencies, FOptionalArrayOfWebhookReward& CallWebhooks, FOptionalArrayOfNewItemReward& AddItems)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AddItemRequests = Serializable->AddItemRequests;
		AddCurrencyMap = Serializable->AddCurrencyMap;
		bApplyVipBonus = Serializable->bApplyVipBonus;
		Description = Serializable->Description;
		ChangeCurrencies = Serializable->ChangeCurrencies;
		CallWebhooks = Serializable->CallWebhooks;
		AddItems = Serializable->AddItems;
	}
		
}

