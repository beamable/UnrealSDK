
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetConfigByCustomerIdRequest.h"

void UApiCustomerGetConfigByCustomerIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiCustomerGetConfigByCustomerIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/config");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiCustomerGetConfigByCustomerIdRequest::BuildBody(FString& BodyString) const
{
	
}

UApiCustomerGetConfigByCustomerIdRequest* UApiCustomerGetConfigByCustomerIdRequest::Make(FString _CustomerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiCustomerGetConfigByCustomerIdRequest* Req = NewObject<UApiCustomerGetConfigByCustomerIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
