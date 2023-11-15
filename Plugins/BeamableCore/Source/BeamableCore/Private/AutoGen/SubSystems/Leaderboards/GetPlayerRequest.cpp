
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetPlayerRequest.h"

void UGetPlayerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPlayerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/leaderboards/player");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("dbid"), *FString::FromInt(Dbid));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPlayerRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPlayerRequest* UGetPlayerRequest::Make(int64 _Dbid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetPlayerRequest* Req = NewObject<UGetPlayerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Dbid = _Dbid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
