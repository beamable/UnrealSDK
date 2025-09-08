
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetAdminViewRequest.h"

void UGetAdminViewRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAdminViewRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/admin-view");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAdminViewRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAdminViewRequest* UGetAdminViewRequest::Make(FString _CustomerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAdminViewRequest* Req = NewObject<UGetAdminViewRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
