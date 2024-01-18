
#include "BeamableCore/Public/AutoGen/SubSystems/Player/PutPresenceStatusRequest.h"

void UPutPresenceStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPresenceStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/players/{playerId}/presence/status");
	Route = Route.Replace(TEXT("{playerId}"), *PlayerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPresenceStatusRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutPresenceStatusRequest* UPutPresenceStatusRequest::Make(FString _PlayerId, FOptionalPresenceStatus _Status, FOptionalString _Description, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPresenceStatusRequest* Req = NewObject<UPutPresenceStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USetPresenceStatusRequestBody>(Req);
	Req->Body->Status = _Status;
	Req->Body->Description = _Description;
	

	return Req;
}
