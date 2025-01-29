
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/ObjectEventPlayersPostClaimByObjectIdRequest.h"

void UObjectEventPlayersPostClaimByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectEventPlayersPostClaimByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/event-players/{objectId}/claim");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectEventPlayersPostClaimByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectEventPlayersPostClaimByObjectIdRequest* UObjectEventPlayersPostClaimByObjectIdRequest::Make(int64 _ObjectId, FString _EventId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectEventPlayersPostClaimByObjectIdRequest* Req = NewObject<UObjectEventPlayersPostClaimByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEventClaimRequestBody>(Req);
	Req->Body->EventId = _EventId;
	

	return Req;
}
