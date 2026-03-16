
#include "BeamableCore/Public/AutoGen/SubSystems/Session/ApiSessionGetStatusRequest.h"

void UApiSessionGetStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiSessionGetStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/sessions/status");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(PlayerIds.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerIds"), *PlayerIds.Val);
		bIsFirstQueryParam = false;
	}

	if(IntervalSecs.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("intervalSecs"), *FString::FromInt(IntervalSecs.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiSessionGetStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UApiSessionGetStatusRequest* UApiSessionGetStatusRequest::Make(FOptionalString _PlayerIds, FOptionalInt64 _IntervalSecs, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiSessionGetStatusRequest* Req = NewObject<UApiSessionGetStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerIds = _PlayerIds;
	Req->IntervalSecs = _IntervalSecs;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
