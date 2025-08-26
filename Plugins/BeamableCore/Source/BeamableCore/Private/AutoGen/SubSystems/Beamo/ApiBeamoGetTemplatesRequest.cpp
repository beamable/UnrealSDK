
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetTemplatesRequest.h"

void UApiBeamoGetTemplatesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetTemplatesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/templates");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetTemplatesRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetTemplatesRequest* UApiBeamoGetTemplatesRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetTemplatesRequest* Req = NewObject<UApiBeamoGetTemplatesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
