
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PostPaymentsRequest.h"

void UPostPaymentsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPaymentsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/payments");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPaymentsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPaymentsRequest* UPostPaymentsRequest::Make(FString _PlayerId, FString _PaymentProvider, UTransactionDetails* _Details, FOptionalString _InitHistoryData, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPaymentsRequest* Req = NewObject<UPostPaymentsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeginPaymentRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	Req->Body->PaymentProvider = _PaymentProvider;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Details = _Details;
	Req->Body->Details->Rename(nullptr, Req);
	Req->Body->InitHistoryData = _InitHistoryData;
	

	return Req;
}
