
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerTicket/GetMatchmakingTicketsRequest.h"

void UGetMatchmakingTicketsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetMatchmakingTicketsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/players/{playerId}/matchmaking/tickets");
	Route = Route.Replace(TEXT("{playerId}"), *PlayerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetMatchmakingTicketsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetMatchmakingTicketsRequest* UGetMatchmakingTicketsRequest::Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetMatchmakingTicketsRequest* Req = NewObject<UGetMatchmakingTicketsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
