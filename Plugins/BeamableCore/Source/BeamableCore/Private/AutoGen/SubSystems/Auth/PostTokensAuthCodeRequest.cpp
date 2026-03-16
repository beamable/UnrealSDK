
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensAuthCodeRequest.h"

void UPostTokensAuthCodeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTokensAuthCodeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/auth-code");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTokensAuthCodeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTokensAuthCodeRequest* UPostTokensAuthCodeRequest::Make(FOptionalString _ClientId, FOptionalString _Code, FOptionalString _RedirectUri, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTokensAuthCodeRequest* Req = NewObject<UPostTokensAuthCodeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAuthV2AuthorizationCodeAuthRequestBody>(Req);
	Req->Body->ClientId = _ClientId;
	Req->Body->Code = _Code;
	Req->Body->RedirectUri = _RedirectUri;
	Req->Body->Scope = _Scope;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	

	return Req;
}
