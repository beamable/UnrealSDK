
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/GetClientSubscriptionsRequest.h"

void UGetClientSubscriptionsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetClientSubscriptionsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/stats/{objectId}/client/subscriptions");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetClientSubscriptionsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetClientSubscriptionsRequest* UGetClientSubscriptionsRequest::Make(FBeamStatsType _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetClientSubscriptionsRequest* Req = NewObject<UGetClientSubscriptionsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
