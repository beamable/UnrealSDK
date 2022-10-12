
#include "GetChampionsRequest.h"

void UGetChampionsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetChampionsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/champions");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("tournamentId"), *TournamentId);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("cycles"), *FString::FromInt(Cycles));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetChampionsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetChampionsRequest* UGetChampionsRequest::MakeGetChampionsRequest(FString _TournamentId, int32 _Cycles, UObject* Outer)
{
	UGetChampionsRequest* Req = NewObject<UGetChampionsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TournamentId = _TournamentId;
	Req->Cycles = _Cycles;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}