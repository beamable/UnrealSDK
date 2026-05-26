
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsFillDeliveryOrdersRequest.h"

void UBeamFarmMsFillDeliveryOrdersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsFillDeliveryOrdersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/FillDeliveryOrders");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsFillDeliveryOrdersRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamFarmMsFillDeliveryOrdersRequest* UBeamFarmMsFillDeliveryOrdersRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsFillDeliveryOrdersRequest* Req = NewObject<UBeamFarmMsFillDeliveryOrdersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
