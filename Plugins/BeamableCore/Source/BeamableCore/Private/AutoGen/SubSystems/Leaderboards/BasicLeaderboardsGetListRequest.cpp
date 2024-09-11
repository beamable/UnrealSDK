
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetListRequest.h"

void UBasicLeaderboardsGetListRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicLeaderboardsGetListRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/leaderboards/list");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Skip.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("skip"), *FString::FromInt(Skip.Val));
		bIsFirstQueryParam = false;
	}

	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	if(Prefix.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("prefix"), *Prefix.Val);
		bIsFirstQueryParam = false;
	}

	if(bIncludePartitions.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("includePartitions"), bIncludePartitions.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicLeaderboardsGetListRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicLeaderboardsGetListRequest* UBasicLeaderboardsGetListRequest::Make(FOptionalInt32 _Skip, FOptionalInt32 _Limit, FOptionalString _Prefix, FOptionalBool _bIncludePartitions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicLeaderboardsGetListRequest* Req = NewObject<UBasicLeaderboardsGetListRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Skip = _Skip;
	Req->Limit = _Limit;
	Req->Prefix = _Prefix;
	Req->bIncludePartitions = _bIncludePartitions;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
