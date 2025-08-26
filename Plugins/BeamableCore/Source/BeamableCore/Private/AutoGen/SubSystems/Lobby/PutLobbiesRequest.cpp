
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutLobbiesRequest.h"

void UPutLobbiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutLobbiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutLobbiesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutLobbiesRequest* UPutLobbiesRequest::Make(FOptionalString _LobbyId, FOptionalMatchType _MatchType, FOptionalDateTime _Created, FOptionalString _Name, FOptionalString _Description, FOptionalBeamGamerTag _Host, FOptionalString _Passcode, FOptionalLobbyRestriction _Restriction, FOptionalInt32 _MaxPlayers, FOptionalArrayOfLobbyPlayer _Players, FOptionalMapOfString _Data, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutLobbiesRequest* Req = NewObject<UPutLobbiesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULobby>(Req);
	Req->Body->LobbyId = _LobbyId;
	Req->Body->MatchType = _MatchType;
	Req->Body->Created = _Created;
	Req->Body->Name = _Name;
	Req->Body->Description = _Description;
	Req->Body->Host = _Host;
	Req->Body->Passcode = _Passcode;
	Req->Body->Restriction = _Restriction;
	Req->Body->MaxPlayers = _MaxPlayers;
	Req->Body->Players = _Players;
	Req->Body->Data = _Data;
	

	return Req;
}
