
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendCampaignPushToPlayerRequest.h"

void UBeamFarmMsSendCampaignPushToPlayerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsSendCampaignPushToPlayerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/SendCampaignPushToPlayer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsSendCampaignPushToPlayerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsSendCampaignPushToPlayerRequest* UBeamFarmMsSendCampaignPushToPlayerRequest::Make(int64 _PlayerId, UPushCampaignRequestBody* _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsSendCampaignPushToPlayerRequest* Req = NewObject<UBeamFarmMsSendCampaignPushToPlayerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USendCampaignPushToPlayerRequestArgs>(Req);
	Req->Body->PlayerId = _PlayerId;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Request = _Request;
	Req->Body->Request->Rename(nullptr, Req);
	

	return Req;
}
