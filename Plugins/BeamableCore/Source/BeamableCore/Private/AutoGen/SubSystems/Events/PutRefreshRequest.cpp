
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutRefreshRequest.h"

void UPutRefreshRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutRefreshRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/events/{objectId}/refresh");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutRefreshRequest::BuildBody(FString& BodyString) const
{
	
}

UPutRefreshRequest* UPutRefreshRequest::Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutRefreshRequest* Req = NewObject<UPutRefreshRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
