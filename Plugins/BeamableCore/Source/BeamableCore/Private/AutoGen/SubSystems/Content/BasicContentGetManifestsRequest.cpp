
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentGetManifestsRequest.h"

void UBasicContentGetManifestsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicContentGetManifestsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifests");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicContentGetManifestsRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicContentGetManifestsRequest* UBasicContentGetManifestsRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicContentGetManifestsRequest* Req = NewObject<UBasicContentGetManifestsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
