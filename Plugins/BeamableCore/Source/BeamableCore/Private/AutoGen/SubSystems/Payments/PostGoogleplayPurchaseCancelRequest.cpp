
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCancelRequest.h"

void UPostGoogleplayPurchaseCancelRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostGoogleplayPurchaseCancelRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/googleplay/purchase/cancel");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostGoogleplayPurchaseCancelRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostGoogleplayPurchaseCancelRequest* UPostGoogleplayPurchaseCancelRequest::Make(int64 _Txid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostGoogleplayPurchaseCancelRequest* Req = NewObject<UPostGoogleplayPurchaseCancelRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCancelPurchaseRequestBody>(Req);
	Req->Body->Txid = _Txid;
	

	return Req;
}
