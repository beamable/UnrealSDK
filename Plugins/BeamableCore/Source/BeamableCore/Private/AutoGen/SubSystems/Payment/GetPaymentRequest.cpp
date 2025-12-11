
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/GetPaymentRequest.h"

void UGetPaymentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPaymentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/payments/{transactionId}");
	Route = Route.Replace(TEXT("{transactionId}"), *FString::Printf(TEXT("%lld"), TransactionId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPaymentRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPaymentRequest* UGetPaymentRequest::Make(int64 _TransactionId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetPaymentRequest* Req = NewObject<UGetPaymentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TransactionId = _TransactionId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
