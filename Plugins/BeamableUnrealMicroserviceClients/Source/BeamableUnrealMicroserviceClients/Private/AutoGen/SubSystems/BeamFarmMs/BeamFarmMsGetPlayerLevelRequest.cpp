
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetPlayerLevelRequest.h"

void UBeamFarmMsGetPlayerLevelRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsGetPlayerLevelRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/GetPlayerLevel");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsGetPlayerLevelRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamFarmMsGetPlayerLevelRequest* UBeamFarmMsGetPlayerLevelRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsGetPlayerLevelRequest* Req = NewObject<UBeamFarmMsGetPlayerLevelRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
