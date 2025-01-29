
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensPasswordRequest.h"

void UPostTokensPasswordRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTokensPasswordRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/password");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTokensPasswordRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTokensPasswordRequest* UPostTokensPasswordRequest::Make(FOptionalString _Email, FOptionalString _Password, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTokensPasswordRequest* Req = NewObject<UPostTokensPasswordRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPasswordAuthRequestBody>(Req);
	Req->Body->Email = _Email;
	Req->Body->Password = _Password;
	Req->Body->Scope = _Scope;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	

	return Req;
}
