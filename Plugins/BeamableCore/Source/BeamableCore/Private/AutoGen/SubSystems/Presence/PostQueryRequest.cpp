
#include "BeamableCore/Public/AutoGen/SubSystems/Presence/PostQueryRequest.h"

void UPostQueryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostQueryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/presence/query");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostQueryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostQueryRequest* UPostQueryRequest::Make(FOptionalArrayOfString _PlayerIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostQueryRequest* Req = NewObject<UPostQueryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UOnlineStatusQuery>(Req);
	Req->Body->PlayerIds = _PlayerIds;
	

	return Req;
}
