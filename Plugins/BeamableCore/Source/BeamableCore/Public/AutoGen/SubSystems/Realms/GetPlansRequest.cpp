
#include "GetPlansRequest.h"

void UGetPlansRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPlansRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/plans");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPlansRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPlansRequest* UGetPlansRequest::MakeGetPlansRequest(UObject* Outer)
{
	UGetPlansRequest* Req = NewObject<UGetPlansRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
