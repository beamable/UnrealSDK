
#include "AutoGen/SubSystems/Tournaments/PostScoreRequest.h"

void UPostScoreRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostScoreRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/score");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostScoreRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostScoreRequest* UPostScoreRequest::Make(FString _TournamentId, double _Score, int64 _PlayerId, FOptionalBool _bIncrement, FOptionalMapOfString _Stats, UObject* RequestOwner)
{
	UPostScoreRequest* Req = NewObject<UPostScoreRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UScoreRequestBody>(Req);
	Req->Body->TournamentId = _TournamentId;
	Req->Body->Score = _Score;
	Req->Body->PlayerId = _PlayerId;
	Req->Body->bIncrement = _bIncrement;
	Req->Body->Stats = _Stats;
	

	return Req;
}