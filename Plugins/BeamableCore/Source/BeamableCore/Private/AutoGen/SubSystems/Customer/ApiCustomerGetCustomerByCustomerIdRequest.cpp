
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetCustomerByCustomerIdRequest.h"

void UApiCustomerGetCustomerByCustomerIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiCustomerGetCustomerByCustomerIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiCustomerGetCustomerByCustomerIdRequest::BuildBody(FString& BodyString) const
{
	
}

UApiCustomerGetCustomerByCustomerIdRequest* UApiCustomerGetCustomerByCustomerIdRequest::Make(FString _CustomerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiCustomerGetCustomerByCustomerIdRequest* Req = NewObject<UApiCustomerGetCustomerByCustomerIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
