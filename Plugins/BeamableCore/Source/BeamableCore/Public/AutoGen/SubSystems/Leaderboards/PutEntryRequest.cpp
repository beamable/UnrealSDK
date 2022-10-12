
#include "PutEntryRequest.h"

void UPutEntryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutEntryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/entry");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutEntryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutEntryRequest* UPutEntryRequest::MakePutEntryRequest(FString _ObjectId, FOptionalDouble _MaxScore, FOptionalMapOfString _Stats, double _Score, FOptionalDouble _MinScore, int64 _Id, FOptionalBool _bIncrement, UObject* Outer)
{
	UPutEntryRequest* Req = NewObject<UPutEntryRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardAddRequestBody>(Req);
	Req->Body->MaxScore = _MaxScore;
	Req->Body->Stats = _Stats;
	Req->Body->Score = _Score;
	Req->Body->MinScore = _MinScore;
	Req->Body->Id = _Id;
	Req->Body->bIncrement = _bIncrement;
	

	return Req;
}
