
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/BasicAnnouncementsGetListRequest.h"

void UBasicAnnouncementsGetListRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicAnnouncementsGetListRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/list");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicAnnouncementsGetListRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicAnnouncementsGetListRequest* UBasicAnnouncementsGetListRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicAnnouncementsGetListRequest* Req = NewObject<UBasicAnnouncementsGetListRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
