
#include "GetSocialRequest.h"

void UGetSocialRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetSocialRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetSocialRequest::BuildBody(FString& BodyString) const
{
	
}

UGetSocialRequest* UGetSocialRequest::MakeGetSocialRequest(TArray<FString> _PlayerIds, UObject* Outer)
{
	UGetSocialRequest* Req = NewObject<UGetSocialRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerIds = _PlayerIds;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
