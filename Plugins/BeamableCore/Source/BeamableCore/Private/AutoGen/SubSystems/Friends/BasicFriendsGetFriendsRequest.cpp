
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/BasicFriendsGetFriendsRequest.h"

void UBasicFriendsGetFriendsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicFriendsGetFriendsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicFriendsGetFriendsRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicFriendsGetFriendsRequest* UBasicFriendsGetFriendsRequest::Make(TArray<FString> _PlayerIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicFriendsGetFriendsRequest* Req = NewObject<UBasicFriendsGetFriendsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerIds = _PlayerIds;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
