
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensExternalRequest.h"

void UPostTokensExternalRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTokensExternalRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/external");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTokensExternalRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTokensExternalRequest* UPostTokensExternalRequest::Make(FOptionalBool _bHasProviderNamespace, FOptionalString _Provider, FOptionalString _ProviderNamespace, FOptionalString _Token, FOptionalAuthV2ChallengeSolution _ChallengeSolution, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTokensExternalRequest* Req = NewObject<UPostTokensExternalRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAuthV2ExternalAuthRequestBody>(Req);
	Req->Body->bHasProviderNamespace = _bHasProviderNamespace;
	Req->Body->Provider = _Provider;
	Req->Body->ProviderNamespace = _ProviderNamespace;
	Req->Body->Token = _Token;
	Req->Body->ChallengeSolution = _ChallengeSolution;
	Req->Body->Scope = _Scope;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	

	return Req;
}
