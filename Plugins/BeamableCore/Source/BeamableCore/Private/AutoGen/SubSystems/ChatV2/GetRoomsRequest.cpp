
#include "AutoGen/SubSystems/ChatV2/GetRoomsRequest.h"

void UGetRoomsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRoomsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/chatV2/{objectId}/rooms");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRoomsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRoomsRequest* UGetRoomsRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UGetRoomsRequest* Req = NewObject<UGetRoomsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
