
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCheckFcmConfigRequest.h"

void UBeamFarmMsCheckFcmConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsCheckFcmConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/CheckFcmConfig");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsCheckFcmConfigRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamFarmMsCheckFcmConfigRequest* UBeamFarmMsCheckFcmConfigRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsCheckFcmConfigRequest* Req = NewObject<UBeamFarmMsCheckFcmConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
