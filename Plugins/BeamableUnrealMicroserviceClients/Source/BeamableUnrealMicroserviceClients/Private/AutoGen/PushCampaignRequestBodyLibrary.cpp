
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PushCampaignRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPushCampaignRequestBodyLibrary::PushCampaignRequestBodyToJsonString(const UPushCampaignRequestBody* Serializable, const bool Pretty)
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

UPushCampaignRequestBody* UPushCampaignRequestBodyLibrary::Make(FString Title, FString Body, FString DeepLink, FString CampaignId, FString NodeId, FString GamerTag, FString AccountId, FString CidPid, FString CampaignData, TArray<UPushOffer*> Offers, UObject* Outer)
{
	auto Serializable = NewObject<UPushCampaignRequestBody>(Outer);
	Serializable->Title = Title;
	Serializable->Body = Body;
	Serializable->DeepLink = DeepLink;
	Serializable->CampaignId = CampaignId;
	Serializable->NodeId = NodeId;
	Serializable->GamerTag = GamerTag;
	Serializable->AccountId = AccountId;
	Serializable->CidPid = CidPid;
	Serializable->CampaignData = CampaignData;
	Serializable->Offers = Offers;
	
	return Serializable;
}

void UPushCampaignRequestBodyLibrary::Break(const UPushCampaignRequestBody* Serializable, FString& Title, FString& Body, FString& DeepLink, FString& CampaignId, FString& NodeId, FString& GamerTag, FString& AccountId, FString& CidPid, FString& CampaignData, TArray<UPushOffer*>& Offers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Title = Serializable->Title;
		Body = Serializable->Body;
		DeepLink = Serializable->DeepLink;
		CampaignId = Serializable->CampaignId;
		NodeId = Serializable->NodeId;
		GamerTag = Serializable->GamerTag;
		AccountId = Serializable->AccountId;
		CidPid = Serializable->CidPid;
		CampaignData = Serializable->CampaignData;
		Offers = Serializable->Offers;
	}
		
}

