
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeliverOrderResultLibrary::DeliverOrderResultToJsonString(const UDeliverOrderResult* Serializable, const bool Pretty)
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

UDeliverOrderResult* UDeliverOrderResultLibrary::Make(FString OrderId, FString RewardCurrencyId, int32 RewardAmount, FString Message, bool bSuccess, UObject* Outer)
{
	auto Serializable = NewObject<UDeliverOrderResult>(Outer);
	Serializable->OrderId = OrderId;
	Serializable->RewardCurrencyId = RewardCurrencyId;
	Serializable->RewardAmount = RewardAmount;
	Serializable->Message = Message;
	Serializable->bSuccess = bSuccess;
	
	return Serializable;
}

void UDeliverOrderResultLibrary::Break(const UDeliverOrderResult* Serializable, FString& OrderId, FString& RewardCurrencyId, int32& RewardAmount, FString& Message, bool& bSuccess)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OrderId = Serializable->OrderId;
		RewardCurrencyId = Serializable->RewardCurrencyId;
		RewardAmount = Serializable->RewardAmount;
		Message = Serializable->Message;
		bSuccess = Serializable->bSuccess;
	}
		
}

