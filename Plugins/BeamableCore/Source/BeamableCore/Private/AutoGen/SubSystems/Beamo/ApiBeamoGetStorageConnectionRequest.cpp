
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetStorageConnectionRequest.h"

void UApiBeamoGetStorageConnectionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetStorageConnectionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/storage/connection");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetStorageConnectionRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetStorageConnectionRequest* UApiBeamoGetStorageConnectionRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetStorageConnectionRequest* Req = NewObject<UApiBeamoGetStorageConnectionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
