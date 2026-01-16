
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/ApiPaymentGetPaymentsRequest.h"

void UApiPaymentGetPaymentsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiPaymentGetPaymentsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/payments");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiPaymentGetPaymentsRequest::BuildBody(FString& BodyString) const
{
	
}

UApiPaymentGetPaymentsRequest* UApiPaymentGetPaymentsRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiPaymentGetPaymentsRequest* Req = NewObject<UApiPaymentGetPaymentsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
