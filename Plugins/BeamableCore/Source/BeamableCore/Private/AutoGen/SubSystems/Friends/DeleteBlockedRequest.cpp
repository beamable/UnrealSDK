
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/DeleteBlockedRequest.h"

void UDeleteBlockedRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteBlockedRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/blocked");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteBlockedRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteBlockedRequest* UDeleteBlockedRequest::Make(FBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteBlockedRequest* Req = NewObject<UDeleteBlockedRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPlayerIdRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
