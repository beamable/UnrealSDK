
#include "GetDetailRequest.h"

void UGetDetailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetDetailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/detail");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("mid"), *FString::FromInt(Mid));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetDetailRequest::BuildBody(FString& BodyString) const
{
	
}

UGetDetailRequest* UGetDetailRequest::MakeGetDetailRequest(int64 _ObjectId, int64 _Mid, UObject* Outer)
{
	UGetDetailRequest* Req = NewObject<UGetDetailRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Mid = _Mid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
