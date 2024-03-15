
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/DeleteSubscribeRequest.h"

void UDeleteSubscribeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteSubscribeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/stats/subscribe");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteSubscribeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteSubscribeRequest* UDeleteSubscribeRequest::Make(FString _Service, FOptionalArrayOfString _Subscriptions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteSubscribeRequest* Req = NewObject<UDeleteSubscribeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStatsUnsubscribeRequestBody>(Req);
	Req->Body->Service = _Service;
	Req->Body->Subscriptions = _Subscriptions;
	

	return Req;
}
