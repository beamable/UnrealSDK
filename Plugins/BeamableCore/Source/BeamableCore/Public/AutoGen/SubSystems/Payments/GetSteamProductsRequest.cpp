
#include "GetSteamProductsRequest.h"

void UGetSteamProductsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetSteamProductsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/steam/products");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("steamId"), *FString::FromInt(SteamId));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetSteamProductsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetSteamProductsRequest* UGetSteamProductsRequest::MakeGetSteamProductsRequest(int64 _SteamId, UObject* Outer)
{
	UGetSteamProductsRequest* Req = NewObject<UGetSteamProductsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->SteamId = _SteamId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
