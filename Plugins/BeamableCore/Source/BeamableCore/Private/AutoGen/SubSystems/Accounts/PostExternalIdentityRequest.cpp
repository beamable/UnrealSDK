
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostExternalIdentityRequest.h"

void UPostExternalIdentityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostExternalIdentityRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/external_identity");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostExternalIdentityRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostExternalIdentityRequest* UPostExternalIdentityRequest::Make(FString _ProviderService, FString _ExternalToken, FOptionalChallengeSolution _ChallengeSolution, FOptionalString _ProviderNamespace, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostExternalIdentityRequest* Req = NewObject<UPostExternalIdentityRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAttachExternalIdentityApiRequestBody>(Req);
	Req->Body->ProviderService = _ProviderService;
	Req->Body->ExternalToken = _ExternalToken;
	Req->Body->ChallengeSolution = _ChallengeSolution;
	Req->Body->ProviderNamespace = _ProviderNamespace;
	

	return Req;
}
