
#include "PostScoreRequest.h"

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

UPostScoreRequest* UPostScoreRequest::MakePostScoreRequest(FString _TournamentId, FOptionalMapOfString _Stats, double _Score, int64 _PlayerId, FOptionalBool _bIncrement, UObject* Outer)
{
	UPostScoreRequest* Req = NewObject<UPostScoreRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UScoreRequestBody>(Req);
	Req->Body->TournamentId = _TournamentId;
	Req->Body->Stats = _Stats;
	Req->Body->Score = _Score;
	Req->Body->PlayerId = _PlayerId;
	Req->Body->bIncrement = _bIncrement;
	

	return Req;
}
