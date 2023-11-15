
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableExternalIdentityRequest.h"

void UGetAvailableExternalIdentityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableExternalIdentityRequest::BuildRoute(FString& RouteString) const
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

void UGetAvailableExternalIdentityRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableExternalIdentityRequest* UGetAvailableExternalIdentityRequest::Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAvailableExternalIdentityRequest* Req = NewObject<UGetAvailableExternalIdentityRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ProviderService = _ProviderService;
	Req->UserId = _UserId;
	Req->ProviderNamespace = _ProviderNamespace;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
