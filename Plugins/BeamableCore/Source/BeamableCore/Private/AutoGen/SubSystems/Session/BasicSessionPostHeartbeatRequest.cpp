
#include "BeamableCore/Public/AutoGen/SubSystems/Session/BasicSessionPostHeartbeatRequest.h"

void UBasicSessionPostHeartbeatRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBasicSessionPostHeartbeatRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/session/heartbeat");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicSessionPostHeartbeatRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicSessionPostHeartbeatRequest* UBasicSessionPostHeartbeatRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicSessionPostHeartbeatRequest* Req = NewObject<UBasicSessionPostHeartbeatRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
