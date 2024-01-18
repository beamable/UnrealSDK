
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PutSubscribeRequest.h"

void UPutSubscribeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutSubscribeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/stats/subscribe");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutSubscribeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutSubscribeRequest* UPutSubscribeRequest::Make(FString _Service, TArray<FString> _Subscriptions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutSubscribeRequest* Req = NewObject<UPutSubscribeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStatsSubscribeRequestBody>(Req);
	Req->Body->Service = _Service;
	Req->Body->Subscriptions = _Subscriptions;
	

	return Req;
}
