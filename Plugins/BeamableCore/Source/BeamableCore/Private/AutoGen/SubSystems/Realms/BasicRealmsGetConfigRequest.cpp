
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetConfigRequest.h"

void UBasicRealmsGetConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicRealmsGetConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/config");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicRealmsGetConfigRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicRealmsGetConfigRequest* UBasicRealmsGetConfigRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicRealmsGetConfigRequest* Req = NewObject<UBasicRealmsGetConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
