
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/AuthenticateRequest.h"

void UAuthenticateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UAuthenticateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/auth/token");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UAuthenticateRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UAuthenticateRequest* UAuthenticateRequest::Make(FString _GrantType, FOptionalBool _bCustomerScoped, FOptionalString _DeviceId, FOptionalString _ProviderService, FOptionalString _Token, FOptionalString _Code, FOptionalString _ExternalToken, FOptionalChallengeSolution _ChallengeSolution, FOptionalString _ProviderNamespace, FOptionalString _RedirectUri, FOptionalString _ThirdParty, FOptionalContextInfo _Context, FOptionalString _RefreshToken, FOptionalString _Username, FOptionalString _ClientId, FOptionalString _Password, FOptionalArrayOfString _Scope, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = _GrantType;
	Req->Body->bCustomerScoped = _bCustomerScoped;
	Req->Body->DeviceId = _DeviceId;
	Req->Body->ProviderService = _ProviderService;
	Req->Body->Token = _Token;
	Req->Body->Code = _Code;
	Req->Body->ExternalToken = _ExternalToken;
	Req->Body->ChallengeSolution = _ChallengeSolution;
	Req->Body->ProviderNamespace = _ProviderNamespace;
	Req->Body->RedirectUri = _RedirectUri;
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->Context = _Context;
	Req->Body->RefreshToken = _RefreshToken;
	Req->Body->Username = _Username;
	Req->Body->ClientId = _ClientId;
	Req->Body->Password = _Password;
	Req->Body->Scope = _Scope;
	Req->Body->InitProperties = _InitProperties;
	

	return Req;
}
