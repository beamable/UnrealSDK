
#include "GetSteamPricesRequest.h"

void UGetSteamPricesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetSteamPricesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/steam/prices");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("steamId"), *FString::FromInt(SteamId));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetSteamPricesRequest::BuildBody(FString& BodyString) const
{
	
}

UGetSteamPricesRequest* UGetSteamPricesRequest::MakeGetSteamPricesRequest(int64 _SteamId, UObject* Outer)
{
	UGetSteamPricesRequest* Req = NewObject<UGetSteamPricesRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->SteamId = _SteamId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}