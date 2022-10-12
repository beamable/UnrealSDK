
#include "GetIsCustomerRequest.h"

void UGetIsCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetIsCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/is-customer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetIsCustomerRequest::BuildBody(FString& BodyString) const
{
	
}

UGetIsCustomerRequest* UGetIsCustomerRequest::MakeGetIsCustomerRequest(UObject* Outer)
{
	UGetIsCustomerRequest* Req = NewObject<UGetIsCustomerRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}