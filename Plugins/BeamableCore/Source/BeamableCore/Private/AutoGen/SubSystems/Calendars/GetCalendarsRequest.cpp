
#include "AutoGen/SubSystems/Calendars/GetCalendarsRequest.h"

void UGetCalendarsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetCalendarsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/calendars/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetCalendarsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetCalendarsRequest* UGetCalendarsRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UGetCalendarsRequest* Req = NewObject<UGetCalendarsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
