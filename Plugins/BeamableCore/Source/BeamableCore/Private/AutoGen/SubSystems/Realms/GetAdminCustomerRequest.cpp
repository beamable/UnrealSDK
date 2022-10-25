
#include "AutoGen/SubSystems/Realms/GetAdminCustomerRequest.h"

void UGetAdminCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAdminCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/admin/customer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAdminCustomerRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAdminCustomerRequest* UGetAdminCustomerRequest::Make(UObject* Outer)
{
	UGetAdminCustomerRequest* Req = NewObject<UGetAdminCustomerRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
