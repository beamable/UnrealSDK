
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPostInviteByIdRequest.h"

void UApiPartyPostInviteByIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UApiPartyPostInviteByIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/invite");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiPartyPostInviteByIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiPartyPostInviteByIdRequest* UApiPartyPostInviteByIdRequest::Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiPartyPostInviteByIdRequest* Req = NewObject<UApiPartyPostInviteByIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UInviteToParty>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
