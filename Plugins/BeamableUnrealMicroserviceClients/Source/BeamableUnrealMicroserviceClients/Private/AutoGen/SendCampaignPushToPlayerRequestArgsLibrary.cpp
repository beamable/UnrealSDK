
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToPlayerRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendCampaignPushToPlayerRequestArgsLibrary::SendCampaignPushToPlayerRequestArgsToJsonString(const USendCampaignPushToPlayerRequestArgs* Serializable, const bool Pretty)
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

USendCampaignPushToPlayerRequestArgs* USendCampaignPushToPlayerRequestArgsLibrary::Make(int64 PlayerId, UPushCampaignRequestBody* Request, UObject* Outer)
{
	auto Serializable = NewObject<USendCampaignPushToPlayerRequestArgs>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Request = Request;
	
	return Serializable;
}

void USendCampaignPushToPlayerRequestArgsLibrary::Break(const USendCampaignPushToPlayerRequestArgs* Serializable, int64& PlayerId, UPushCampaignRequestBody*& Request)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Request = Serializable->Request;
	}
		
}

