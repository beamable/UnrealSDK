
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetRewardsRequest.h"

void UGetRewardsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRewardsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/rewards");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(TournamentId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("tournamentId"), *TournamentId.Val);
		bIsFirstQueryParam = false;
	}

	if(ContentId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("contentId"), *ContentId.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRewardsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRewardsRequest* UGetRewardsRequest::Make(FOptionalString _TournamentId, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRewardsRequest* Req = NewObject<UGetRewardsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TournamentId = _TournamentId;
	Req->ContentId = _ContentId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
