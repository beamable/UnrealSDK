
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetCustomersRequest.h"

void UBasicRealmsGetCustomersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicRealmsGetCustomersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customers");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicRealmsGetCustomersRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicRealmsGetCustomersRequest* UBasicRealmsGetCustomersRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicRealmsGetCustomersRequest* Req = NewObject<UBasicRealmsGetCustomersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
