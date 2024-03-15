
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPromoteRequest.h"

void UPutPromoteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPromoteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/promote");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPromoteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutPromoteRequest* UPutPromoteRequest::Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPromoteRequest* Req = NewObject<UPutPromoteRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPromoteNewLeader>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
