
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensRefreshTokenRequest.h"

void UPostTokensRefreshTokenRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTokensRefreshTokenRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/refresh-token");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTokensRefreshTokenRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTokensRefreshTokenRequest* UPostTokensRefreshTokenRequest::Make(FOptionalString _RefreshToken, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTokensRefreshTokenRequest* Req = NewObject<UPostTokensRefreshTokenRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URefreshTokenAuthRequestBody>(Req);
	Req->Body->RefreshToken = _RefreshToken;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	

	return Req;
}
