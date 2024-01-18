
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteExternalIdentityRequest.h"

void UDeleteExternalIdentityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteExternalIdentityRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/external_identity");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteExternalIdentityRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteExternalIdentityRequest* UDeleteExternalIdentityRequest::Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteExternalIdentityRequest* Req = NewObject<UDeleteExternalIdentityRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteExternalIdentityApiRequestBody>(Req);
	Req->Body->ProviderService = _ProviderService;
	Req->Body->UserId = _UserId;
	Req->Body->ProviderNamespace = _ProviderNamespace;
	

	return Req;
}
