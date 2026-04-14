
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostAuthCodesRequest.h"

void UPostAuthCodesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostAuthCodesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/auth-codes");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostAuthCodesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostAuthCodesRequest* UPostAuthCodesRequest::Make(FOptionalBeamAccountId _AccountId, FOptionalString _RedirectUri, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, FOptionalArrayOfString _Scopes, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostAuthCodesRequest* Req = NewObject<UPostAuthCodesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAuthV2AuthCodeRequestBody>(Req);
	Req->Body->AccountId = _AccountId;
	Req->Body->RedirectUri = _RedirectUri;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	Req->Body->Scopes = _Scopes;
	

	return Req;
}
