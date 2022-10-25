
#include "AutoGen/SubSystems/Announcements/GetRawRequest.h"

void UGetRawRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRawRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/announcements/{objectId}/raw");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRawRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRawRequest* UGetRawRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UGetRawRequest* Req = NewObject<UGetRawRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
