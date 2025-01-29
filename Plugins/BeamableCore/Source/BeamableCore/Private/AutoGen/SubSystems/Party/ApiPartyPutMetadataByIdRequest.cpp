
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutMetadataByIdRequest.h"

void UApiPartyPutMetadataByIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UApiPartyPutMetadataByIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}/metadata");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiPartyPutMetadataByIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiPartyPutMetadataByIdRequest* UApiPartyPutMetadataByIdRequest::Make(FGuid _Id, FOptionalString _Restriction, FOptionalInt32 _MaxSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiPartyPutMetadataByIdRequest* Req = NewObject<UApiPartyPutMetadataByIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateParty>(Req);
	Req->Body->Restriction = _Restriction;
	Req->Body->MaxSize = _MaxSize;
	

	return Req;
}
