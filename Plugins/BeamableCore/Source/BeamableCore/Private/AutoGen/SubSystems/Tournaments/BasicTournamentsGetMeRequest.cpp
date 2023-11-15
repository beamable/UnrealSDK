
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/BasicTournamentsGetMeRequest.h"

void UBasicTournamentsGetMeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicTournamentsGetMeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/me");
	
	
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

	if(bHasUnclaimedRewards.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("hasUnclaimedRewards"), bHasUnclaimedRewards.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicTournamentsGetMeRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicTournamentsGetMeRequest* UBasicTournamentsGetMeRequest::Make(FOptionalString _TournamentId, FOptionalString _ContentId, FOptionalBool _bHasUnclaimedRewards, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicTournamentsGetMeRequest* Req = NewObject<UBasicTournamentsGetMeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TournamentId = _TournamentId;
	Req->ContentId = _ContentId;
	Req->bHasUnclaimedRewards = _bHasUnclaimedRewards;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
