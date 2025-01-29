
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/ApiMatchmakingGetMatchesByIdRequest.h"

void UApiMatchmakingGetMatchesByIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiMatchmakingGetMatchesByIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/matchmaking/matches/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiMatchmakingGetMatchesByIdRequest::BuildBody(FString& BodyString) const
{
	
}

UApiMatchmakingGetMatchesByIdRequest* UApiMatchmakingGetMatchesByIdRequest::Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiMatchmakingGetMatchesByIdRequest* Req = NewObject<UApiMatchmakingGetMatchesByIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
