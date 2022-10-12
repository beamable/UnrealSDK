
#include "GetItemsRequest.h"

void UGetItemsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetItemsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/inventory/items");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetItemsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetItemsRequest* UGetItemsRequest::MakeGetItemsRequest(UObject* Outer)
{
	UGetItemsRequest* Req = NewObject<UGetItemsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
