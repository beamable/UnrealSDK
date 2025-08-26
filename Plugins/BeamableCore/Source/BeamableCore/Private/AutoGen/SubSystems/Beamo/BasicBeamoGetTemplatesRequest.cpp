
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetTemplatesRequest.h"

void UBasicBeamoGetTemplatesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicBeamoGetTemplatesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/templates");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicBeamoGetTemplatesRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicBeamoGetTemplatesRequest* UBasicBeamoGetTemplatesRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicBeamoGetTemplatesRequest* Req = NewObject<UBasicBeamoGetTemplatesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
