
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPostServerRequest.h"

void UApiLobbyPostServerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UApiLobbyPostServerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies/{id}/server");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiLobbyPostServerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiLobbyPostServerRequest* UApiLobbyPostServerRequest::Make(FGuid _Id, FOptionalBeamContentId _MatchType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiLobbyPostServerRequest* Req = NewObject<UApiLobbyPostServerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateFederatedGameServer>(Req);
	Req->Body->MatchType = _MatchType;
	

	return Req;
}
