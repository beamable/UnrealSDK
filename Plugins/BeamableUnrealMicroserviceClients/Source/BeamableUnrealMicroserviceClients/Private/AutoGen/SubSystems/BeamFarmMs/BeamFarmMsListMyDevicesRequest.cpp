
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsListMyDevicesRequest.h"

void UBeamFarmMsListMyDevicesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsListMyDevicesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/ListMyDevices");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsListMyDevicesRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamFarmMsListMyDevicesRequest* UBeamFarmMsListMyDevicesRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsListMyDevicesRequest* Req = NewObject<UBeamFarmMsListMyDevicesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
