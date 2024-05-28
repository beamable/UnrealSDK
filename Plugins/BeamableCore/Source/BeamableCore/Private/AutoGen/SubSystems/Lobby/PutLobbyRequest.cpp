
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutLobbyRequest.h"

void UPutLobbyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutLobbyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutLobbyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutLobbyRequest* UPutLobbyRequest::Make(FGuid _Id, FOptionalString _Passcode, FOptionalArrayOfBeamTag _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutLobbyRequest* Req = NewObject<UPutLobbyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UJoinLobby>(Req);
	Req->Body->Passcode = _Passcode;
	Req->Body->Tags = _Tags;
	

	return Req;
}
