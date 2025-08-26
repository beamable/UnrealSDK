
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetGamesRequest.h"

void UBasicRealmsGetGamesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicRealmsGetGamesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/games");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicRealmsGetGamesRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicRealmsGetGamesRequest* UBasicRealmsGetGamesRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicRealmsGetGamesRequest* Req = NewObject<UBasicRealmsGetGamesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
