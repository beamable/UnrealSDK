
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsDeliverOrderRequest.h"

void UBeamFarmMsDeliverOrderRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsDeliverOrderRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/DeliverOrder");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsDeliverOrderRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsDeliverOrderRequest* UBeamFarmMsDeliverOrderRequest::Make(FString _OrderId, int64 _ItemInstanceId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsDeliverOrderRequest* Req = NewObject<UBeamFarmMsDeliverOrderRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeliverOrderRequestArgs>(Req);
	Req->Body->OrderId = _OrderId;
	Req->Body->ItemInstanceId = _ItemInstanceId;
	

	return Req;
}
