
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/ApiAuthPostServerRequest.h"

void UApiAuthPostServerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UApiAuthPostServerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/server");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiAuthPostServerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UApiAuthPostServerRequest* UApiAuthPostServerRequest::Make(FOptionalString _ClientId, FOptionalString _ClientSecret, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiAuthPostServerRequest* Req = NewObject<UApiAuthPostServerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UServerTokenAuthRequestBody>(Req);
	Req->Body->ClientId = _ClientId;
	Req->Body->ClientSecret = _ClientSecret;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	

	return Req;
}
