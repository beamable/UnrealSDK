
#include "BeamableCore/Public/AutoGen/SubSystems/Session/ApiSessionPostHeartbeatRequest.h"

void UApiSessionPostHeartbeatRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UApiSessionPostHeartbeatRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/sessions/heartbeat");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiSessionPostHeartbeatRequest::BuildBody(FString& BodyString) const
{
	
}

UApiSessionPostHeartbeatRequest* UApiSessionPostHeartbeatRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiSessionPostHeartbeatRequest* Req = NewObject<UApiSessionPostHeartbeatRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
