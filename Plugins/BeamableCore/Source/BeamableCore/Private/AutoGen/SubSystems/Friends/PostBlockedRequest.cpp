
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/PostBlockedRequest.h"

void UPostBlockedRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostBlockedRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/blocked");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostBlockedRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostBlockedRequest* UPostBlockedRequest::Make(FBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostBlockedRequest* Req = NewObject<UPostBlockedRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPlayerIdRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
