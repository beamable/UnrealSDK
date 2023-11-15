
#include "BeamableCore/Public/AutoGen/SubSystems/Session/BasicSessionGetStatusRequest.h"

void UBasicSessionGetStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicSessionGetStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/session/status");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerIds"), *PlayerIds);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("intervalSecs"), *FString::FromInt(IntervalSecs));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicSessionGetStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicSessionGetStatusRequest* UBasicSessionGetStatusRequest::Make(FString _PlayerIds, int64 _IntervalSecs, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicSessionGetStatusRequest* Req = NewObject<UBasicSessionGetStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerIds = _PlayerIds;
	Req->IntervalSecs = _IntervalSecs;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
