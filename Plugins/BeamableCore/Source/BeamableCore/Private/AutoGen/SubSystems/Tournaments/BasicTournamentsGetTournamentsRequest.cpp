
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/BasicTournamentsGetTournamentsRequest.h"

void UBasicTournamentsGetTournamentsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicTournamentsGetTournamentsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(bIsRunning.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("isRunning"), bIsRunning.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	if(ContentId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("contentId"), *ContentId.Val);
		bIsFirstQueryParam = false;
	}

	if(Cycle.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("cycle"), *FString::FromInt(Cycle.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicTournamentsGetTournamentsRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicTournamentsGetTournamentsRequest* UBasicTournamentsGetTournamentsRequest::Make(FOptionalBool _bIsRunning, FOptionalString _ContentId, FOptionalInt32 _Cycle, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicTournamentsGetTournamentsRequest* Req = NewObject<UBasicTournamentsGetTournamentsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->bIsRunning = _bIsRunning;
	Req->ContentId = _ContentId;
	Req->Cycle = _Cycle;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
