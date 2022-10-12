
#include "GetProjectPromoteRequest.h"

void UGetProjectPromoteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetProjectPromoteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project/promote");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("sourcePid"), *SourcePid);
	bIsFirstQueryParam = false;
	
	if(Promotions.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		bIsFirstQueryParam = false;
	}

	if(ContentManifestIds.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetProjectPromoteRequest::BuildBody(FString& BodyString) const
{
	
}

UGetProjectPromoteRequest* UGetProjectPromoteRequest::MakeGetProjectPromoteRequest(FString _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* Outer)
{
	UGetProjectPromoteRequest* Req = NewObject<UGetProjectPromoteRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->SourcePid = _SourcePid;
	Req->Promotions = _Promotions;
	Req->ContentManifestIds = _ContentManifestIds;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}