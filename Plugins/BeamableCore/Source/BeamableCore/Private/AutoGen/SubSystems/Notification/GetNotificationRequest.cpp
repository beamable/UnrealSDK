
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/GetNotificationRequest.h"

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

UGetNotificationRequest* UGetNotificationRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetNotificationRequest* Req = NewObject<UGetNotificationRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
