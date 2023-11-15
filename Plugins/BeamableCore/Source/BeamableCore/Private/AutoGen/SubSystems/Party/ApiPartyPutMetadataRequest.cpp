
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutMetadataRequest.h"

void UApiPartyPutMetadataRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UApiPartyPutMetadataRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/metadata");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiPartyPutMetadataRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiPartyPutMetadataRequest* UApiPartyPutMetadataRequest::Make(FGuid _Id, FOptionalString _Restriction, FOptionalInt32 _MaxSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiPartyPutMetadataRequest* Req = NewObject<UApiPartyPutMetadataRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateParty>(Req);
	Req->Body->Restriction = _Restriction;
	Req->Body->MaxSize = _MaxSize;
	

	return Req;
}
