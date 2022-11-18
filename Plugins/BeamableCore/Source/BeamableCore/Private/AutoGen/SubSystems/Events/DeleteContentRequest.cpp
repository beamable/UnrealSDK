
#include "AutoGen/SubSystems/Events/DeleteContentRequest.h"

void UDeleteContentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteContentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/events/{objectId}/content");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteContentRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteContentRequest* UDeleteContentRequest::Make(FString _ObjectId, UObject* RequestOwner)
{
	UDeleteContentRequest* Req = NewObject<UDeleteContentRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
