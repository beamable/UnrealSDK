
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetContentRequest.h"

void UBasicAnnouncementsGetContentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicAnnouncementsGetContentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/content");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicAnnouncementsGetContentRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicAnnouncementsGetContentRequest* UBasicAnnouncementsGetContentRequest::Make(UObject* Outer)
{
	UBasicAnnouncementsGetContentRequest* Req = NewObject<UBasicAnnouncementsGetContentRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
