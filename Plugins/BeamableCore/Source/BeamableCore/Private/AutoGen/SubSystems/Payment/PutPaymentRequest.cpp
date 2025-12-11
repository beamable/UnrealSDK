
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PutPaymentRequest.h"

void UPutPaymentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPaymentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/payments/{transactionId}");
	Route = Route.Replace(TEXT("{transactionId}"), *FString::Printf(TEXT("%lld"), TransactionId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPaymentRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutPaymentRequest* UPutPaymentRequest::Make(int64 _TransactionId, FString _PaymentProvider, FString _Receipt, FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPaymentRequest* Req = NewObject<UPutPaymentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TransactionId = _TransactionId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCompletePaymentRequestBody>(Req);
	Req->Body->PaymentProvider = _PaymentProvider;
	Req->Body->Receipt = _Receipt;
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
