
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetStatusRequest.h"

void UApiBeamoGetStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/status");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetStatusRequest* UApiBeamoGetStatusRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetStatusRequest* Req = NewObject<UApiBeamoGetStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
