
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/DeletePaymentRequest.h"

void UDeletePaymentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeletePaymentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/payments/{transactionId}");
	Route = Route.Replace(TEXT("{transactionId}"), *FString::Printf(TEXT("%lld"), TransactionId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeletePaymentRequest::BuildBody(FString& BodyString) const
{
	
}

UDeletePaymentRequest* UDeletePaymentRequest::Make(int64 _TransactionId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeletePaymentRequest* Req = NewObject<UDeletePaymentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TransactionId = _TransactionId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
