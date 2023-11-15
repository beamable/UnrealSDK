
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostHeartbeatRequest.h"

void UPostHeartbeatRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostHeartbeatRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/session/heartbeat");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostHeartbeatRequest::BuildBody(FString& BodyString) const
{
	
}

UPostHeartbeatRequest* UPostHeartbeatRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostHeartbeatRequest* Req = NewObject<UPostHeartbeatRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
