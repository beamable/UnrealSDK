
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/DeleteEntryRequest.h"

void UDeleteEntryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteEntryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/entry");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteEntryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteEntryRequest* UDeleteEntryRequest::Make(FString _ObjectId, int64 _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteEntryRequest* Req = NewObject<UDeleteEntryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardRemoveEntryRequestBody>(Req);
	Req->Body->Id = _Id;
	

	return Req;
}
