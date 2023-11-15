
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetRanksRequest.h"

void UGetRanksRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRanksRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/ranks");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("ids"), *Ids);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRanksRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRanksRequest* UGetRanksRequest::Make(FString _ObjectId, FString _Ids, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRanksRequest* Req = NewObject<UGetRanksRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Ids = _Ids;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
