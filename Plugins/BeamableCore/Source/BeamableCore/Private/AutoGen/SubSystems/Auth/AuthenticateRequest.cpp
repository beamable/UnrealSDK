
#include "AutoGen/SubSystems/Auth/AuthenticateRequest.h"

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

UAuthenticateRequest* UAuthenticateRequest::Make(FString _GrantType, FOptionalBool _bCustomerScoped, FOptionalString _DeviceId, FOptionalString _Username, FOptionalString _RefreshToken, FOptionalContextInfo _Context, FOptionalString _ThirdParty, FOptionalString _RedirectUri, FOptionalString _ClientId, FOptionalString _Code, FOptionalString _Token, FOptionalString _Password, FOptionalArrayOfString _Scope, UObject* Outer)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = _GrantType;
	Req->Body->bCustomerScoped = _bCustomerScoped;
	Req->Body->DeviceId = _DeviceId;
	Req->Body->Username = _Username;
	Req->Body->RefreshToken = _RefreshToken;
	Req->Body->Context = _Context;
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->RedirectUri = _RedirectUri;
	Req->Body->ClientId = _ClientId;
	Req->Body->Code = _Code;
	Req->Body->Token = _Token;
	Req->Body->Password = _Password;
	Req->Body->Scope = _Scope;
	

	return Req;
}
