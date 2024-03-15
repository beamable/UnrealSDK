
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseCancelRequest.h"

void UPostFacebookPurchaseCancelRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostFacebookPurchaseCancelRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/facebook/purchase/cancel");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostFacebookPurchaseCancelRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostFacebookPurchaseCancelRequest* UPostFacebookPurchaseCancelRequest::Make(int64 _Txid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostFacebookPurchaseCancelRequest* Req = NewObject<UPostFacebookPurchaseCancelRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCancelPurchaseRequestBody>(Req);
	Req->Body->Txid = _Txid;
	

	return Req;
}
