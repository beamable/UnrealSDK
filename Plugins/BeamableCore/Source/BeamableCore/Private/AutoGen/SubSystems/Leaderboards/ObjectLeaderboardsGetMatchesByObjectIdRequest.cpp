
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetMatchesByObjectIdRequest.h"

void UObjectLeaderboardsGetMatchesByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectLeaderboardsGetMatchesByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/matches");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("poolSize"), *FString::FromInt(PoolSize));
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("windows"), *FString::FromInt(Windows));
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("windowSize"), *FString::FromInt(WindowSize));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectLeaderboardsGetMatchesByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectLeaderboardsGetMatchesByObjectIdRequest* UObjectLeaderboardsGetMatchesByObjectIdRequest::Make(FString _ObjectId, int32 _PoolSize, int32 _Windows, int32 _WindowSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectLeaderboardsGetMatchesByObjectIdRequest* Req = NewObject<UObjectLeaderboardsGetMatchesByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->PoolSize = _PoolSize;
	Req->Windows = _Windows;
	Req->WindowSize = _WindowSize;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
