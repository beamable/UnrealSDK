
#include "BeamableCore/Public/AutoGen/SubSystems/Events/BasicEventsGetContentRequest.h"

void UBasicEventsGetContentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicEventsGetContentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/events/content");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicEventsGetContentRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicEventsGetContentRequest* UBasicEventsGetContentRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicEventsGetContentRequest* Req = NewObject<UBasicEventsGetContentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
