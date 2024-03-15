
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeleteInviteRequest.h"

void UDeleteInviteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteInviteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/invite");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteInviteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteInviteRequest* UDeleteInviteRequest::Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteInviteRequest* Req = NewObject<UDeleteInviteRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCancelInviteToParty>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
