
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PutEntryRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutEntryRequest* UPutEntryRequest::Make(FString _ObjectId, double _Score, int64 _Id, FOptionalBool _bIncrement, FOptionalDouble _MaxScore, FOptionalDouble _MinScore, FOptionalMapOfString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutEntryRequest* Req = NewObject<UPutEntryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardAddRequestBody>(Req);
	Req->Body->Score = _Score;
	Req->Body->Id = _Id;
	Req->Body->bIncrement = _bIncrement;
	Req->Body->MaxScore = _MaxScore;
	Req->Body->MinScore = _MinScore;
	Req->Body->Stats = _Stats;
	

	return Req;
}
