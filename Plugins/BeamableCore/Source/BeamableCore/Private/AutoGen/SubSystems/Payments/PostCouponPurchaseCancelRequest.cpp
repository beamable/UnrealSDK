
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseCancelRequest.h"

void UPostCouponPurchaseCancelRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostCouponPurchaseCancelRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/coupon/purchase/cancel");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostCouponPurchaseCancelRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCouponPurchaseCancelRequest* UPostCouponPurchaseCancelRequest::Make(int64 _Txid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostCouponPurchaseCancelRequest* Req = NewObject<UPostCouponPurchaseCancelRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCancelPurchaseRequestBody>(Req);
	Req->Body->Txid = _Txid;
	

	return Req;
}
