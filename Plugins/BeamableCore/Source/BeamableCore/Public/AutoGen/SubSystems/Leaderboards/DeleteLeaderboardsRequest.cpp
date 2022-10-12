
#include "DeleteLeaderboardsRequest.h"

void UDeleteLeaderboardsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteLeaderboardsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteLeaderboardsRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteLeaderboardsRequest* UDeleteLeaderboardsRequest::MakeDeleteLeaderboardsRequest(FString _ObjectId, UObject* Outer)
{
	UDeleteLeaderboardsRequest* Req = NewObject<UDeleteLeaderboardsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
