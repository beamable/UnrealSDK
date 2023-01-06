
#include "AutoGen/SubSystems/Accounts/DeleteExternal_identityRequest.h"

void UDeleteExternal_identityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteExternal_identityRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/external_identity");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteExternal_identityRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteExternal_identityRequest* UDeleteExternal_identityRequest::Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner)
{
	UDeleteExternal_identityRequest* Req = NewObject<UDeleteExternal_identityRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteExternalIdentityApiRequestBody>(Req);
	Req->Body->ProviderService = _ProviderService;
	Req->Body->UserId = _UserId;
	Req->Body->ProviderNamespace = _ProviderNamespace;
	

	return Req;
}
