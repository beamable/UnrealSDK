
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerLobby/DeleteLobbiesRequest.h"

void UDeleteLobbiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteLobbiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/players/{playerId}/lobbies");
	Route = Route.Replace(TEXT("{playerId}"), *PlayerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteLobbiesRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteLobbiesRequest* UDeleteLobbiesRequest::Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteLobbiesRequest* Req = NewObject<UDeleteLobbiesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
