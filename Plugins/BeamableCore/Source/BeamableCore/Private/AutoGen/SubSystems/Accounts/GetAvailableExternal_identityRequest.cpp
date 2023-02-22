
#include "AutoGen/SubSystems/Accounts/GetAvailableExternal_identityRequest.h"

void UGetAvailableExternal_identityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableExternal_identityRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/available/external_identity");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("provider_service"), *ProviderService);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("user_id"), *UserId);
	bIsFirstQueryParam = false;
	
	if(ProviderNamespace.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("provider_namespace"), *ProviderNamespace.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailableExternal_identityRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableExternal_identityRequest* UGetAvailableExternal_identityRequest::Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner)
{
	UGetAvailableExternal_identityRequest* Req = NewObject<UGetAvailableExternal_identityRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ProviderService = _ProviderService;
	Req->UserId = _UserId;
	Req->ProviderNamespace = _ProviderNamespace;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
