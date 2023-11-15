
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableThirdPartyRequest.h"

void UGetAvailableThirdPartyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableThirdPartyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/available/third-party");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("thirdParty"), *ThirdParty);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("token"), *Token);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailableThirdPartyRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableThirdPartyRequest* UGetAvailableThirdPartyRequest::Make(FString _ThirdParty, FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAvailableThirdPartyRequest* Req = NewObject<UGetAvailableThirdPartyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ThirdParty = _ThirdParty;
	Req->Token = _Token;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
