
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseFailRequest.h"

void UPostSteamPurchaseFailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSteamPurchaseFailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/steam/purchase/fail");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSteamPurchaseFailRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSteamPurchaseFailRequest* UPostSteamPurchaseFailRequest::Make(int64 _Txid, FString _Reason, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSteamPurchaseFailRequest* Req = NewObject<UPostSteamPurchaseFailRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UFailPurchaseRequestBody>(Req);
	Req->Body->Txid = _Txid;
	Req->Body->Reason = _Reason;
	

	return Req;
}
