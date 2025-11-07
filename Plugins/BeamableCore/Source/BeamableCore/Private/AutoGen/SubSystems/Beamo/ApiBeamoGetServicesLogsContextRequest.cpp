
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetServicesLogsContextRequest.h"

void UApiBeamoGetServicesLogsContextRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetServicesLogsContextRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/logs/context");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetServicesLogsContextRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetServicesLogsContextRequest* UApiBeamoGetServicesLogsContextRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetServicesLogsContextRequest* Req = NewObject<UApiBeamoGetServicesLogsContextRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
