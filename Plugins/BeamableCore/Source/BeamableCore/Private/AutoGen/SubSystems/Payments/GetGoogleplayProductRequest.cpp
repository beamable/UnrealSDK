
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetGoogleplayProductRequest.h"

void UGetGoogleplayProductRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetGoogleplayProductRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/googleplay/product");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("sku"), *Sku);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetGoogleplayProductRequest::BuildBody(FString& BodyString) const
{
	
}

UGetGoogleplayProductRequest* UGetGoogleplayProductRequest::Make(FString _Sku, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetGoogleplayProductRequest* Req = NewObject<UGetGoogleplayProductRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Sku = _Sku;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
