
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseBeginRequest.h"

void UPostFacebookPurchaseBeginRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostFacebookPurchaseBeginRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/facebook/purchase/begin");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostFacebookPurchaseBeginRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostFacebookPurchaseBeginRequest* UPostFacebookPurchaseBeginRequest::Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* Outer)
{
	UPostFacebookPurchaseBeginRequest* Req = NewObject<UPostFacebookPurchaseBeginRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeginPurchaseRequestBody>(Req);
	Req->Body->PurchaseId = _PurchaseId;
	Req->Body->Language = _Language;
	Req->Body->Time = _Time;
	

	return Req;
}
