
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetRunningRequest.h"

void UGetRunningRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRunningRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/events/running");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRunningRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRunningRequest* UGetRunningRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRunningRequest* Req = NewObject<UGetRunningRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
