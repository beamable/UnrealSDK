
#include "GetListTagsRequest.h"

void UGetListTagsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetListTagsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/list/tags");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(TagNameFilter.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("tagNameFilter"), *TagNameFilter.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetListTagsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetListTagsRequest* UGetListTagsRequest::MakeGetListTagsRequest(FOptionalString _TagNameFilter, UObject* Outer)
{
	UGetListTagsRequest* Req = NewObject<UGetListTagsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TagNameFilter = _TagNameFilter;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
