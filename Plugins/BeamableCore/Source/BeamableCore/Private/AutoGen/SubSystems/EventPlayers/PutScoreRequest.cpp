
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/PutScoreRequest.h"

void UPutScoreRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutScoreRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/event-players/{objectId}/score");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutScoreRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutScoreRequest* UPutScoreRequest::Make(int64 _ObjectId, FString _EventId, double _Score, FOptionalBool _bIncrement, FOptionalMapOfString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutScoreRequest* Req = NewObject<UPutScoreRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEventScoreRequestBody>(Req);
	Req->Body->EventId = _EventId;
	Req->Body->Score = _Score;
	Req->Body->bIncrement = _bIncrement;
	Req->Body->Stats = _Stats;
	

	return Req;
}
