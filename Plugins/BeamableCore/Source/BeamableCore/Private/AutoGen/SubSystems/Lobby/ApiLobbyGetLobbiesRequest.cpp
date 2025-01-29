
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyGetLobbiesRequest.h"

void UApiLobbyGetLobbiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiLobbyGetLobbiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/lobbies");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
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

	if(MatchType.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("MatchType"), *static_cast<FString>(MatchType.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiLobbyGetLobbiesRequest::BuildBody(FString& BodyString) const
{
	
}

UApiLobbyGetLobbiesRequest* UApiLobbyGetLobbiesRequest::Make(FOptionalInt32 _Skip, FOptionalInt32 _Limit, FOptionalBeamContentId _MatchType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiLobbyGetLobbiesRequest* Req = NewObject<UApiLobbyGetLobbiesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Skip = _Skip;
	Req->Limit = _Limit;
	Req->MatchType = _MatchType;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
