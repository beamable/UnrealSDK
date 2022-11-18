
#include "AutoGen/SubSystems/Accounts/PostExternal_identityRequest.h"

void UPostExternal_identityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostExternal_identityRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/external_identity");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostExternal_identityRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostExternal_identityRequest* UPostExternal_identityRequest::Make(FString _ProviderAddress, FString _ExternalToken, FOptionalChallengeSolution _ChallengeSolution, UObject* RequestOwner)
{
	UPostExternal_identityRequest* Req = NewObject<UPostExternal_identityRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UExternalIdentityRequestBody>(Req);
	Req->Body->ProviderAddress = _ProviderAddress;
	Req->Body->ExternalToken = _ExternalToken;
	Req->Body->ChallengeSolution = _ChallengeSolution;
	

	return Req;
}
