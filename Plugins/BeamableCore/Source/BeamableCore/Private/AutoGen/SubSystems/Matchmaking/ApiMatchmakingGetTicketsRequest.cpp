
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/ApiMatchmakingGetTicketsRequest.h"

void UApiMatchmakingGetTicketsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiMatchmakingGetTicketsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/matchmaking/tickets");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Players.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		bIsFirstQueryParam = false;
	}

	if(bIncludeInactive.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("IncludeInactive"), bIncludeInactive.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	if(Skip.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("Skip"), *FString::FromInt(Skip.Val));
		bIsFirstQueryParam = false;
	}

	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("Limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiMatchmakingGetTicketsRequest::BuildBody(FString& BodyString) const
{
	
}

UApiMatchmakingGetTicketsRequest* UApiMatchmakingGetTicketsRequest::Make(FOptionalArrayOfBeamGamerTag _Players, FOptionalBool _bIncludeInactive, FOptionalInt32 _Skip, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiMatchmakingGetTicketsRequest* Req = NewObject<UApiMatchmakingGetTicketsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Players = _Players;
	Req->bIncludeInactive = _bIncludeInactive;
	Req->Skip = _Skip;
	Req->Limit = _Limit;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
