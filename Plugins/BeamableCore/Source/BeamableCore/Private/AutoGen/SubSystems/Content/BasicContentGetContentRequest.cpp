
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentGetContentRequest.h"

void UBasicContentGetContentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicContentGetContentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/content");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("contentId"), *static_cast<FString>(ContentId));
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("version"), *Version);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicContentGetContentRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicContentGetContentRequest* UBasicContentGetContentRequest::Make(FBeamContentId _ContentId, FString _Version, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicContentGetContentRequest* Req = NewObject<UBasicContentGetContentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ContentId = _ContentId;
	Req->Version = _Version;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
