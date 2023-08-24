
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeleteMembersRequest.h"

void UDeleteMembersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteMembersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/members");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteMembersRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteMembersRequest* UDeleteMembersRequest::Make(FGuid _Id, FOptionalString _PlayerId, UObject* RequestOwner)
{
	UDeleteMembersRequest* Req = NewObject<UDeleteMembersRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaveParty>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}