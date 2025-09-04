
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetCustomersRequest.h"

void UApiCustomerGetCustomersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiCustomerGetCustomersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiCustomerGetCustomersRequest::BuildBody(FString& BodyString) const
{
	
}

UApiCustomerGetCustomersRequest* UApiCustomerGetCustomersRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiCustomerGetCustomersRequest* Req = NewObject<UApiCustomerGetCustomersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
