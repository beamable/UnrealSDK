
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetStatusRequest.h"

void UBasicBeamoGetStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicBeamoGetStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/status");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicBeamoGetStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicBeamoGetStatusRequest* UBasicBeamoGetStatusRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicBeamoGetStatusRequest* Req = NewObject<UBasicBeamoGetStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
