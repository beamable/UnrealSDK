
#include "GetDetailsRequest.h"

void UGetDetailsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetDetailsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/details");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(From.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("from"), *FString::FromInt(From.Val));
		bIsFirstQueryParam = false;
	}

	if(Max.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("max"), *FString::FromInt(Max.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetDetailsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetDetailsRequest* UGetDetailsRequest::MakeGetDetailsRequest(FString _ObjectId, FOptionalInt32 _From, FOptionalInt32 _Max, UObject* Outer)
{
	UGetDetailsRequest* Req = NewObject<UGetDetailsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->From = _From;
	Req->Max = _Max;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}