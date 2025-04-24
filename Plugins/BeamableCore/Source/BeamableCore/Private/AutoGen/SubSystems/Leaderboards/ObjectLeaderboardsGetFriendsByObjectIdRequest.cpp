
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetFriendsByObjectIdRequest.h"

void UObjectLeaderboardsGetFriendsByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectLeaderboardsGetFriendsByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/friends");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectLeaderboardsGetFriendsByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectLeaderboardsGetFriendsByObjectIdRequest* UObjectLeaderboardsGetFriendsByObjectIdRequest::Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectLeaderboardsGetFriendsByObjectIdRequest* Req = NewObject<UObjectLeaderboardsGetFriendsByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
