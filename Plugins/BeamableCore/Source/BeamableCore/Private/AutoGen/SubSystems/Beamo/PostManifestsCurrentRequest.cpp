
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestsCurrentRequest.h"

void UPostManifestsCurrentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestsCurrentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/manifests/current");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestsCurrentRequest::BuildBody(FString& BodyString) const
{
	
}

UPostManifestsCurrentRequest* UPostManifestsCurrentRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostManifestsCurrentRequest* Req = NewObject<UPostManifestsCurrentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
