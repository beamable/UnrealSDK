
#include "AutoGen/SubSystems/Beamo/GetStatusRequest.h"

void UGetStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/status");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UGetStatusRequest* UGetStatusRequest::Make(UObject* RequestOwner)
{
	UGetStatusRequest* Req = NewObject<UGetStatusRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
