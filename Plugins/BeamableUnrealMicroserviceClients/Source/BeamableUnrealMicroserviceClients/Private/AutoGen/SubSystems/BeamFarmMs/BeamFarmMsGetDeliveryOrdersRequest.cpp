
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetDeliveryOrdersRequest.h"

void UBeamFarmMsGetDeliveryOrdersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsGetDeliveryOrdersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/GetDeliveryOrders");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsGetDeliveryOrdersRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamFarmMsGetDeliveryOrdersRequest* UBeamFarmMsGetDeliveryOrdersRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsGetDeliveryOrdersRequest* Req = NewObject<UBeamFarmMsGetDeliveryOrdersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
