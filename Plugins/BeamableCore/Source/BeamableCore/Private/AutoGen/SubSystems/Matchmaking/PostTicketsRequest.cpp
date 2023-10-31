
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/PostTicketsRequest.h"

void UPostTicketsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTicketsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/matchmaking/tickets");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTicketsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTicketsRequest* UPostTicketsRequest::Make(FOptionalBool _bWatchOnlineStatus, FOptionalBeamContentId _MatchTypes, FOptionalInt32 _MaxWaitDurationSecs, FOptionalString _Team, FOptionalArrayOfString _Players, UObject* RequestOwner)
{
	UPostTicketsRequest* Req = NewObject<UPostTicketsRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTicketReservationRequestBody>(Req);
	Req->Body->bWatchOnlineStatus = _bWatchOnlineStatus;
	Req->Body->MatchTypes = _MatchTypes;
	Req->Body->MaxWaitDurationSecs = _MaxWaitDurationSecs;
	Req->Body->Team = _Team;
	Req->Body->Players = _Players;
	

	return Req;
}
