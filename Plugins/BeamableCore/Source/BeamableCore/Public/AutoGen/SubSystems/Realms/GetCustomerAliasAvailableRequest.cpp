
#include "GetCustomerAliasAvailableRequest.h"

void UGetCustomerAliasAvailableRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetCustomerAliasAvailableRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customer/alias/available");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("alias"), *Alias);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetCustomerAliasAvailableRequest::BuildBody(FString& BodyString) const
{
	
}

UGetCustomerAliasAvailableRequest* UGetCustomerAliasAvailableRequest::MakeGetCustomerAliasAvailableRequest(FString _Alias, UObject* Outer)
{
	UGetCustomerAliasAvailableRequest* Req = NewObject<UGetCustomerAliasAvailableRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Alias = _Alias;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
