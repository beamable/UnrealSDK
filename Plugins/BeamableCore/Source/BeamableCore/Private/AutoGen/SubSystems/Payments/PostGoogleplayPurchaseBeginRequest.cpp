
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostGoogleplayPurchaseBeginRequest.h"

void UPostGoogleplayPurchaseBeginRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostGoogleplayPurchaseBeginRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/googleplay/purchase/begin");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostGoogleplayPurchaseBeginRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostGoogleplayPurchaseBeginRequest* UPostGoogleplayPurchaseBeginRequest::Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostGoogleplayPurchaseBeginRequest* Req = NewObject<UPostGoogleplayPurchaseBeginRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeginPurchaseRequestBody>(Req);
	Req->Body->PurchaseId = _PurchaseId;
	Req->Body->Language = _Language;
	Req->Body->Time = _Time;
	

	return Req;
}
