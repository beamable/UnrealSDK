
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetGamesRequest.h"

void UGetGamesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetGamesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/games");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetGamesRequest::BuildBody(FString& BodyString) const
{
	
}

UGetGamesRequest* UGetGamesRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetGamesRequest* Req = NewObject<UGetGamesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
