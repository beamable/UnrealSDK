
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetSteamOrderRequest.h"

void UGetSteamOrderRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetSteamOrderRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/steam/order");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("orderId"), *OrderId);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetSteamOrderRequest::BuildBody(FString& BodyString) const
{
	
}

UGetSteamOrderRequest* UGetSteamOrderRequest::Make(FString _OrderId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetSteamOrderRequest* Req = NewObject<UGetSteamOrderRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->OrderId = _OrderId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
