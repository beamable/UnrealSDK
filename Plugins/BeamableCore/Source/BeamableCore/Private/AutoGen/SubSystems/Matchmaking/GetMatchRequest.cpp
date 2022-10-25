
#include "AutoGen/SubSystems/Matchmaking/GetMatchRequest.h"

void UGetMatchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetMatchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/matchmaking/{objectId}/match");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetMatchRequest::BuildBody(FString& BodyString) const
{
	
}

UGetMatchRequest* UGetMatchRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UGetMatchRequest* Req = NewObject<UGetMatchRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
