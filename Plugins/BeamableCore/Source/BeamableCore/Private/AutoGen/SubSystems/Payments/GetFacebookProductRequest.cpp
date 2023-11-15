
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetFacebookProductRequest.h"

void UGetFacebookProductRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetFacebookProductRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/facebook/product");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("sku"), *Sku);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetFacebookProductRequest::BuildBody(FString& BodyString) const
{
	
}

UGetFacebookProductRequest* UGetFacebookProductRequest::Make(FString _Sku, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetFacebookProductRequest* Req = NewObject<UGetFacebookProductRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Sku = _Sku;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
