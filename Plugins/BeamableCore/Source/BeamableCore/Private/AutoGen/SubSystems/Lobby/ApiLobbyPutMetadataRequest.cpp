
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataRequest.h"

void UApiLobbyPutMetadataRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UApiLobbyPutMetadataRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies/{id}/metadata");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiLobbyPutMetadataRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiLobbyPutMetadataRequest* UApiLobbyPutMetadataRequest::Make(FGuid _Id, FOptionalString _Name, FOptionalString _Description, FOptionalString _Restriction, FOptionalBeamContentId _MatchType, FOptionalInt32 _MaxPlayers, FOptionalString _NewHost, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiLobbyPutMetadataRequest* Req = NewObject<UApiLobbyPutMetadataRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateLobby>(Req);
	Req->Body->Name = _Name;
	Req->Body->Description = _Description;
	Req->Body->Restriction = _Restriction;
	Req->Body->MatchType = _MatchType;
	Req->Body->MaxPlayers = _MaxPlayers;
	Req->Body->NewHost = _NewHost;
	

	return Req;
}
