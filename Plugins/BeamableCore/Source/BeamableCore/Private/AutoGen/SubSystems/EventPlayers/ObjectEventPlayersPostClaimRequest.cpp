
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/ObjectEventPlayersPostClaimRequest.h"

void UObjectEventPlayersPostClaimRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectEventPlayersPostClaimRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/event-players/{objectId}/claim");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectEventPlayersPostClaimRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectEventPlayersPostClaimRequest* UObjectEventPlayersPostClaimRequest::Make(int64 _ObjectId, FString _EventId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectEventPlayersPostClaimRequest* Req = NewObject<UObjectEventPlayersPostClaimRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEventClaimRequestBody>(Req);
	Req->Body->EventId = _EventId;
	

	return Req;
}
