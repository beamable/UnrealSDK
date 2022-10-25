
#include "AutoGen/SubSystems/Leaderboards/GetUidRequest.h"

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

UGetUidRequest* UGetUidRequest::Make(UObject* Outer)
{
	UGetUidRequest* Req = NewObject<UGetUidRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
