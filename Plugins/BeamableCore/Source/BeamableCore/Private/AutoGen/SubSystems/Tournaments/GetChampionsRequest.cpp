
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetChampionsRequest.h"

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
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("tournamentId"), *TournamentId);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("cycles"), *FString::FromInt(Cycles));
	bIsFirstQueryParam = false;
	
	if(ContentId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("contentId"), *ContentId.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetChampionsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetChampionsRequest* UGetChampionsRequest::Make(FString _TournamentId, int32 _Cycles, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetChampionsRequest* Req = NewObject<UGetChampionsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TournamentId = _TournamentId;
	Req->Cycles = _Cycles;
	Req->ContentId = _ContentId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
