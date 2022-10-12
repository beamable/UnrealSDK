
#include "AuthenticateRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UAuthenticateRequest* UAuthenticateRequest::MakeAuthenticateRequest(FOptionalString _DeviceId, FOptionalString _Username, FOptionalArrayOfString _Scope, FOptionalString _RefreshToken, FOptionalContextInfo _Context, FOptionalString _ThirdParty, FOptionalString _RedirectUri, FOptionalString _ClientId, FOptionalString _Code, FOptionalString _Token, FOptionalBool _bCustomerScoped, FString _GrantType, FOptionalString _Password, UObject* Outer)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->DeviceId = _DeviceId;
	Req->Body->Username = _Username;
	Req->Body->Scope = _Scope;
	Req->Body->RefreshToken = _RefreshToken;
	Req->Body->Context = _Context;
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->RedirectUri = _RedirectUri;
	Req->Body->ClientId = _ClientId;
	Req->Body->Code = _Code;
	Req->Body->Token = _Token;
	Req->Body->bCustomerScoped = _bCustomerScoped;
	Req->Body->GrantType = _GrantType;
	Req->Body->Password = _Password;
	

	return Req;
}
