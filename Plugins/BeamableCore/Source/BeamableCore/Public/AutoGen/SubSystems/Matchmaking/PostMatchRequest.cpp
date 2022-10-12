
#include "PostMatchRequest.h"

void UPostMatchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostMatchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/matchmaking/{objectId}/match");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostMatchRequest::BuildBody(FString& BodyString) const
{
	
}

UPostMatchRequest* UPostMatchRequest::MakePostMatchRequest(int64 _ObjectId, UObject* Outer)
{
	UPostMatchRequest* Req = NewObject<UPostMatchRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
