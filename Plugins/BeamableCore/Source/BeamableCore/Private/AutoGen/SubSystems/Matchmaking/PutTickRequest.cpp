
#include "AutoGen/SubSystems/Matchmaking/PutTickRequest.h"

void UPutTickRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutTickRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/matchmaking/{objectId}/tick");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutTickRequest::BuildBody(FString& BodyString) const
{
	
}

UPutTickRequest* UPutTickRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UPutTickRequest* Req = NewObject<UPutTickRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
