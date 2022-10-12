
#include "PutFreezeRequest.h"

void UPutFreezeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutFreezeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/freeze");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutFreezeRequest::BuildBody(FString& BodyString) const
{
	
}

UPutFreezeRequest* UPutFreezeRequest::MakePutFreezeRequest(FString _ObjectId, UObject* Outer)
{
	UPutFreezeRequest* Req = NewObject<UPutFreezeRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
