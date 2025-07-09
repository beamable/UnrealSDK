
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetManifestsByManifestIdRequest.h"

void UApiBeamoGetManifestsByManifestIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetManifestsByManifestIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/manifests/{manifestId}");
	Route = Route.Replace(TEXT("{id}"), *ManifestId.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(bArchived.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("archived"), bArchived.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetManifestsByManifestIdRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetManifestsByManifestIdRequest* UApiBeamoGetManifestsByManifestIdRequest::Make(FGuid _ManifestId, FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetManifestsByManifestIdRequest* Req = NewObject<UApiBeamoGetManifestsByManifestIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ManifestId = _ManifestId;
	Req->bArchived = _bArchived;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
