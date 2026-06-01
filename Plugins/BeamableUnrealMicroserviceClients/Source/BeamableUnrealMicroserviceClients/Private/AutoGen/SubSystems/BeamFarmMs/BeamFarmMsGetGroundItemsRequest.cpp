
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetGroundItemsRequest.h"

void UBeamFarmMsGetGroundItemsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsGetGroundItemsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/GetGroundItems");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsGetGroundItemsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsGetGroundItemsRequest* UBeamFarmMsGetGroundItemsRequest::Make(FString _SpawnerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsGetGroundItemsRequest* Req = NewObject<UBeamFarmMsGetGroundItemsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetGroundItemsRequestArgs>(Req);
	Req->Body->SpawnerId = _SpawnerId;
	

	return Req;
}
