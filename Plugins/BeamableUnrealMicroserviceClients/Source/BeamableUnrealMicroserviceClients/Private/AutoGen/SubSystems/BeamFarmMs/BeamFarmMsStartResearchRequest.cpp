
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsStartResearchRequest.h"

void UBeamFarmMsStartResearchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsStartResearchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/StartResearch");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsStartResearchRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsStartResearchRequest* UBeamFarmMsStartResearchRequest::Make(int64 _ItemInstanceId, FString _ItemContentId, FString _ProjectContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsStartResearchRequest* Req = NewObject<UBeamFarmMsStartResearchRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStartResearchRequestArgs>(Req);
	Req->Body->ItemInstanceId = _ItemInstanceId;
	Req->Body->ItemContentId = _ItemContentId;
	Req->Body->ProjectContentId = _ProjectContentId;
	

	return Req;
}
