
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutCustomerRequest.h"

void UPutCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutCustomerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutCustomerRequest* UPutCustomerRequest::Make(FString _CustomerId, FOptionalPaymentStatus _PaymentStatus, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutCustomerRequest* Req = NewObject<UPutCustomerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateCustomerRequestBody>(Req);
	Req->Body->PaymentStatus = _PaymentStatus;
	

	return Req;
}
