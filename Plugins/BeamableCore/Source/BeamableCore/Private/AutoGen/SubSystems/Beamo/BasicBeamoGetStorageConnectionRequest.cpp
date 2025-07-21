
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetStorageConnectionRequest.h"

void UBasicBeamoGetStorageConnectionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicBeamoGetStorageConnectionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/storage/connection");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicBeamoGetStorageConnectionRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicBeamoGetStorageConnectionRequest* UBasicBeamoGetStorageConnectionRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicBeamoGetStorageConnectionRequest* Req = NewObject<UBasicBeamoGetStorageConnectionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
