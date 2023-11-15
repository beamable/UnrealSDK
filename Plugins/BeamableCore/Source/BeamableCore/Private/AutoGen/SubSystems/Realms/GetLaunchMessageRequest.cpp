
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetLaunchMessageRequest.h"

void UGetLaunchMessageRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetLaunchMessageRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/launch-message");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetLaunchMessageRequest::BuildBody(FString& BodyString) const
{
	
}

UGetLaunchMessageRequest* UGetLaunchMessageRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetLaunchMessageRequest* Req = NewObject<UGetLaunchMessageRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
