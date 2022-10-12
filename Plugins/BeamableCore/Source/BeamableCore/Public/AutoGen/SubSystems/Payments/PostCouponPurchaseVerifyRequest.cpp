
#include "PostCouponPurchaseVerifyRequest.h"

void UPostCouponPurchaseVerifyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostCouponPurchaseVerifyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/coupon/purchase/verify");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostCouponPurchaseVerifyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCouponPurchaseVerifyRequest* UPostCouponPurchaseVerifyRequest::MakePostCouponPurchaseVerifyRequest(FString _Receipt, UObject* Outer)
{
	UPostCouponPurchaseVerifyRequest* Req = NewObject<UPostCouponPurchaseVerifyRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UVerifyPurchaseRequestBody>(Req);
	Req->Body->Receipt = _Receipt;
	

	return Req;
}