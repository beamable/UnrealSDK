
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PostLobbiesRequest.h"

void UPostLobbiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostLobbiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostLobbiesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostLobbiesRequest* UPostLobbiesRequest::Make(FOptionalString _Name, FOptionalString _Description, FOptionalString _Restriction, FOptionalBeamContentId _MatchType, FOptionalInt32 _PasscodeLength, FOptionalInt32 _MaxPlayers, FOptionalArrayOfTag _PlayerTags, UObject* RequestOwner)
{
	UPostLobbiesRequest* Req = NewObject<UPostLobbiesRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateLobby>(Req);
	Req->Body->Name = _Name;
	Req->Body->Description = _Description;
	Req->Body->Restriction = _Restriction;
	Req->Body->MatchType = _MatchType;
	Req->Body->PasscodeLength = _PasscodeLength;
	Req->Body->MaxPlayers = _MaxPlayers;
	Req->Body->PlayerTags = _PlayerTags;
	

	return Req;
}
