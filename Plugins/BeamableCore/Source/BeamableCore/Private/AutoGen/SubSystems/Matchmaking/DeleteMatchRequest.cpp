
#include "AutoGen/SubSystems/Matchmaking/DeleteMatchRequest.h"

void UDeleteMatchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteMatchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/matchmaking/{objectId}/match");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteMatchRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteMatchRequest* UDeleteMatchRequest::Make(int64 _ObjectId, UObject* RequestOwner)
{
	UDeleteMatchRequest* Req = NewObject<UDeleteMatchRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
