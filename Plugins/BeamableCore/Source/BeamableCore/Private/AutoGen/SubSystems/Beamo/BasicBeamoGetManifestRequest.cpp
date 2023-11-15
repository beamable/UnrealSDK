
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetManifestRequest.h"

void UBasicBeamoGetManifestRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicBeamoGetManifestRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/manifest");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("id"), *Id);
	bIsFirstQueryParam = false;
	
	if(bArchived.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("archived"), bArchived.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicBeamoGetManifestRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicBeamoGetManifestRequest* UBasicBeamoGetManifestRequest::Make(FString _Id, FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicBeamoGetManifestRequest* Req = NewObject<UBasicBeamoGetManifestRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	Req->bArchived = _bArchived;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
