
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToSelfRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendCampaignPushToSelfRequestArgsLibrary::SendCampaignPushToSelfRequestArgsToJsonString(const USendCampaignPushToSelfRequestArgs* Serializable, const bool Pretty)
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

USendCampaignPushToSelfRequestArgs* USendCampaignPushToSelfRequestArgsLibrary::Make(UPushCampaignRequestBody* Request, UObject* Outer)
{
	auto Serializable = NewObject<USendCampaignPushToSelfRequestArgs>(Outer);
	Serializable->Request = Request;
	
	return Serializable;
}

void USendCampaignPushToSelfRequestArgsLibrary::Break(const USendCampaignPushToSelfRequestArgs* Serializable, UPushCampaignRequestBody*& Request)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Request = Serializable->Request;
	}
		
}

