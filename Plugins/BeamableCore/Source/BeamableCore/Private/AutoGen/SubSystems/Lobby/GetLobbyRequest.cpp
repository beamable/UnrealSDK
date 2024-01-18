
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/GetLobbyRequest.h"

void UGetLobbyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetLobbyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetLobbyRequest::BuildBody(FString& BodyString) const
{
	
}

UGetLobbyRequest* UGetLobbyRequest::Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetLobbyRequest* Req = NewObject<UGetLobbyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
