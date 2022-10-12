
#include "PostFacebookPurchaseFailRequest.h"

void UPostFacebookPurchaseFailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostFacebookPurchaseFailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/facebook/purchase/fail");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostFacebookPurchaseFailRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostFacebookPurchaseFailRequest* UPostFacebookPurchaseFailRequest::MakePostFacebookPurchaseFailRequest(int64 _Txid, FString _Reason, UObject* Outer)
{
	UPostFacebookPurchaseFailRequest* Req = NewObject<UPostFacebookPurchaseFailRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UFailPurchaseRequestBody>(Req);
	Req->Body->Txid = _Txid;
	Req->Body->Reason = _Reason;
	

	return Req;
}