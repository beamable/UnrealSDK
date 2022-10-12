
#include "GetRecommendedRequest.h"

void UGetRecommendedRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRecommendedRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/recommended");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRecommendedRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRecommendedRequest* UGetRecommendedRequest::MakeGetRecommendedRequest(int64 _ObjectId, UObject* Outer)
{
	UGetRecommendedRequest* Req = NewObject<UGetRecommendedRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}