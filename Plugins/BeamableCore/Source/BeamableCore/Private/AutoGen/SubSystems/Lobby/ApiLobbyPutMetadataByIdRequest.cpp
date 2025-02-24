
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataByIdRequest.h"

void UApiLobbyPutMetadataByIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UApiLobbyPutMetadataByIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies/{id}/metadata");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiLobbyPutMetadataByIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiLobbyPutMetadataByIdRequest* UApiLobbyPutMetadataByIdRequest::Make(FGuid _Id, FOptionalString _Name, FOptionalString _Description, FOptionalLobbyRestriction _Restriction, FOptionalBeamContentId _MatchType, FOptionalInt32 _MaxPlayers, FOptionalString _NewHost, FOptionalUpdateData _Data, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiLobbyPutMetadataByIdRequest* Req = NewObject<UApiLobbyPutMetadataByIdRequest>(RequestOwner);
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
	Req->Body->Data = _Data;
	

	return Req;
}
