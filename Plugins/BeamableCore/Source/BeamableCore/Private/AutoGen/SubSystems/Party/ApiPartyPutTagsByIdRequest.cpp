
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutTagsByIdRequest.h"

void UApiPartyPutTagsByIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UApiPartyPutTagsByIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/tags");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiPartyPutTagsByIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiPartyPutTagsByIdRequest* UApiPartyPutTagsByIdRequest::Make(FGuid _Id, FOptionalString _PlayerId, FOptionalArrayOfBeamTag _MemberTags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiPartyPutTagsByIdRequest* Req = NewObject<UApiPartyPutTagsByIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdatePartyTags>(Req);
	Req->Body->PlayerId = _PlayerId;
	Req->Body->MemberTags = _MemberTags;
	

	return Req;
}
