
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/GetOtelViewsRequest.h"

void UGetOtelViewsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetOtelViewsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/otel/views");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(PlayerId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerId"), *PlayerId.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetOtelViewsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetOtelViewsRequest* UGetOtelViewsRequest::Make(FOptionalString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetOtelViewsRequest* Req = NewObject<UGetOtelViewsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
