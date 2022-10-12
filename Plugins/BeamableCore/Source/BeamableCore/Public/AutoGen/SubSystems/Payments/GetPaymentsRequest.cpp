
#include "GetPaymentsRequest.h"

void UGetPaymentsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPaymentsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/payments/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPaymentsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPaymentsRequest* UGetPaymentsRequest::MakeGetPaymentsRequest(int64 _ObjectId, UObject* Outer)
{
	UGetPaymentsRequest* Req = NewObject<UGetPaymentsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
