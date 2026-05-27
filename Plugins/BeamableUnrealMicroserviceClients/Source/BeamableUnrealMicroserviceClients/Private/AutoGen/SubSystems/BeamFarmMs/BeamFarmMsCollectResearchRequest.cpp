
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectResearchRequest.h"

void UBeamFarmMsCollectResearchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsCollectResearchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/CollectResearch");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsCollectResearchRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsCollectResearchRequest* UBeamFarmMsCollectResearchRequest::Make(int64 _ItemInstanceId, FString _ItemContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsCollectResearchRequest* Req = NewObject<UBeamFarmMsCollectResearchRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCollectResearchRequestArgs>(Req);
	Req->Body->ItemInstanceId = _ItemInstanceId;
	Req->Body->ItemContentId = _ItemContentId;
	

	return Req;
}
