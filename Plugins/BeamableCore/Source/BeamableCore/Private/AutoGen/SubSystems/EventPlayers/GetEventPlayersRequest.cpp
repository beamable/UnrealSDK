
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/GetEventPlayersRequest.h"

void UGetEventPlayersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetEventPlayersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/event-players/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetEventPlayersRequest::BuildBody(FString& BodyString) const
{
	
}

UGetEventPlayersRequest* UGetEventPlayersRequest::Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetEventPlayersRequest* Req = NewObject<UGetEventPlayersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
