
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetTokenRequest.h"

void UGetTokenRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetTokenRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/auth/token");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("token"), *Token);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetTokenRequest::BuildBody(FString& BodyString) const
{
	
}

UGetTokenRequest* UGetTokenRequest::Make(FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetTokenRequest* Req = NewObject<UGetTokenRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Token = _Token;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
