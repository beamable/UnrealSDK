
#include "AutoGen/SubSystems/Notification/GetNotificationRequest.h"

void UGetNotificationRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetNotificationRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/notification/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetNotificationRequest::BuildBody(FString& BodyString) const
{
	
}

UGetNotificationRequest* UGetNotificationRequest::Make(UObject* Outer)
{
	UGetNotificationRequest* Req = NewObject<UGetNotificationRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
