
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetUidRequest.h"

void UGetUidRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetUidRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/leaderboards/uid");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetUidRequest::BuildBody(FString& BodyString) const
{
	
}

UGetUidRequest* UGetUidRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetUidRequest* Req = NewObject<UGetUidRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
