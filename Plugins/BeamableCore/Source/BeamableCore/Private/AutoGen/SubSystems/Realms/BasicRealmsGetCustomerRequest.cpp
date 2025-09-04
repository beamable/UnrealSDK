
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetCustomerRequest.h"

void UBasicRealmsGetCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicRealmsGetCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicRealmsGetCustomerRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicRealmsGetCustomerRequest* UBasicRealmsGetCustomerRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicRealmsGetCustomerRequest* Req = NewObject<UBasicRealmsGetCustomerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
