
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PatchPaymentRequest.h"

void UPatchPaymentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PATCH");
}

void UPatchPaymentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/payments/{transactionId}");
	Route = Route.Replace(TEXT("{transactionId}"), *FString::Printf(TEXT("%lld"), TransactionId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPatchPaymentRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPatchPaymentRequest* UPatchPaymentRequest::Make(int64 _TransactionId, EBeamTransactionState _State, FOptionalString _Reason, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPatchPaymentRequest* Req = NewObject<UPatchPaymentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TransactionId = _TransactionId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdatePaymentRequestBody>(Req);
	Req->Body->State = _State;
	Req->Body->Reason = _Reason;
	

	return Req;
}
