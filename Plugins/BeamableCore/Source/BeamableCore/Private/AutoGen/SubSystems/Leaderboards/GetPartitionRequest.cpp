
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetPartitionRequest.h"

void UGetPartitionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPartitionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/partition");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerId"), *FString::FromInt(PlayerId));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPartitionRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPartitionRequest* UGetPartitionRequest::Make(FString _ObjectId, int64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetPartitionRequest* Req = NewObject<UGetPartitionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
