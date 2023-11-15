
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetPingRequest.h"

void UGetPingRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPingRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/events/{objectId}/ping");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPingRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPingRequest* UGetPingRequest::Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetPingRequest* Req = NewObject<UGetPingRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
