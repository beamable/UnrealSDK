
#include "GetMyRequest.h"

void UGetMyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetMyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/my");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetMyRequest::BuildBody(FString& BodyString) const
{
	
}

UGetMyRequest* UGetMyRequest::MakeGetMyRequest(UObject* Outer)
{
	UGetMyRequest* Req = NewObject<UGetMyRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
