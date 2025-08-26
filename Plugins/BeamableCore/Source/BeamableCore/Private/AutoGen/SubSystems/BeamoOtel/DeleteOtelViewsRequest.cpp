
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/DeleteOtelViewsRequest.h"

void UDeleteOtelViewsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteOtelViewsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/otel/views/{viewId}");
	Route = Route.Replace(TEXT("{viewId}"), *ViewId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteOtelViewsRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteOtelViewsRequest* UDeleteOtelViewsRequest::Make(FString _ViewId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteOtelViewsRequest* Req = NewObject<UDeleteOtelViewsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ViewId = _ViewId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
