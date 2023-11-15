
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetItemsRequest.h"

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

UGetItemsRequest* UGetItemsRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetItemsRequest* Req = NewObject<UGetItemsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
