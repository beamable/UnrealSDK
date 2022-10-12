
#include "GetCustomerRequest.h"

void UGetCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetCustomerRequest::BuildBody(FString& BodyString) const
{
	
}

UGetCustomerRequest* UGetCustomerRequest::MakeGetCustomerRequest(UObject* Outer)
{
	UGetCustomerRequest* Req = NewObject<UGetCustomerRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
