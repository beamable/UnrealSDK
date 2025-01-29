
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetAssignmentByObjectIdRequest.h"

void UObjectLeaderboardsGetAssignmentByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectLeaderboardsGetAssignmentByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/assignment");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectLeaderboardsGetAssignmentByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectLeaderboardsGetAssignmentByObjectIdRequest* UObjectLeaderboardsGetAssignmentByObjectIdRequest::Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectLeaderboardsGetAssignmentByObjectIdRequest* Req = NewObject<UObjectLeaderboardsGetAssignmentByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
