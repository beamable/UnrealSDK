
#include "GetEventPlayersRequest.h"

void UGetEventPlayersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetEventPlayersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/event-players/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetEventPlayersRequest::BuildBody(FString& BodyString) const
{
	
}

UGetEventPlayersRequest* UGetEventPlayersRequest::MakeGetEventPlayersRequest(int64 _ObjectId, UObject* Outer)
{
	UGetEventPlayersRequest* Req = NewObject<UGetEventPlayersRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
