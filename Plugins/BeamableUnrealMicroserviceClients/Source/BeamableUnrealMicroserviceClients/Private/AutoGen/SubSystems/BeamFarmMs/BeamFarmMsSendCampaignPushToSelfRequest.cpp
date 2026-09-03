
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendCampaignPushToSelfRequest.h"

void UBeamFarmMsSendCampaignPushToSelfRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsSendCampaignPushToSelfRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/SendCampaignPushToSelf");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsSendCampaignPushToSelfRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsSendCampaignPushToSelfRequest* UBeamFarmMsSendCampaignPushToSelfRequest::Make(UPushCampaignRequestBody* _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsSendCampaignPushToSelfRequest* Req = NewObject<UBeamFarmMsSendCampaignPushToSelfRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USendCampaignPushToSelfRequestArgs>(Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Request = _Request;
	Req->Body->Request->Rename(nullptr, Req);
	

	return Req;
}
