
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetFacebookUpdateRequest.h"

void UGetFacebookUpdateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetFacebookUpdateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/facebook/update");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("hubMode"), *HubMode);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("hubChallenge"), *HubChallenge);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("hubVerifyToken"), *HubVerifyToken);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetFacebookUpdateRequest::BuildBody(FString& BodyString) const
{
	
}

UGetFacebookUpdateRequest* UGetFacebookUpdateRequest::Make(FString _HubMode, FString _HubChallenge, FString _HubVerifyToken, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetFacebookUpdateRequest* Req = NewObject<UGetFacebookUpdateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->HubMode = _HubMode;
	Req->HubChallenge = _HubChallenge;
	Req->HubVerifyToken = _HubVerifyToken;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
