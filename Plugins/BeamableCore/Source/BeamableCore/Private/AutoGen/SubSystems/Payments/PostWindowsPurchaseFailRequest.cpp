
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseFailRequest.h"

void UPostWindowsPurchaseFailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostWindowsPurchaseFailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/windows/purchase/fail");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostWindowsPurchaseFailRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostWindowsPurchaseFailRequest* UPostWindowsPurchaseFailRequest::Make(int64 _Txid, FString _Reason, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostWindowsPurchaseFailRequest* Req = NewObject<UPostWindowsPurchaseFailRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UFailPurchaseRequestBody>(Req);
	Req->Body->Txid = _Txid;
	Req->Body->Reason = _Reason;
	

	return Req;
}
