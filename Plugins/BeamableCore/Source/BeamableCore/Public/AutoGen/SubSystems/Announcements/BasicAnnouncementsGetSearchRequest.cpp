
#include "BasicAnnouncementsGetSearchRequest.h"

void UBasicAnnouncementsGetSearchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicAnnouncementsGetSearchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/search");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Date.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("date"), *Date.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicAnnouncementsGetSearchRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicAnnouncementsGetSearchRequest* UBasicAnnouncementsGetSearchRequest::MakeBasicAnnouncementsGetSearchRequest(FOptionalString _Date, UObject* Outer)
{
	UBasicAnnouncementsGetSearchRequest* Req = NewObject<UBasicAnnouncementsGetSearchRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Date = _Date;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
