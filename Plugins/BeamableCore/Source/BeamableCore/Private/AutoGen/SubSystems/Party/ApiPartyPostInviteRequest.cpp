
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPostInviteRequest.h"

void UApiPartyPostInviteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UApiPartyPostInviteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/invite");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiPartyPostInviteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiPartyPostInviteRequest* UApiPartyPostInviteRequest::Make(FGuid _Id, FOptionalString _PlayerId, UObject* RequestOwner)
{
	UApiPartyPostInviteRequest* Req = NewObject<UApiPartyPostInviteRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UInviteToParty>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
