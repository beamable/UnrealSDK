
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/BasicAccountsGetSearchRequest.h"

void UBasicAccountsGetSearchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicAccountsGetSearchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/search");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("query"), *Query);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("page"), *FString::FromInt(Page));
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("pagesize"), *FString::FromInt(Pagesize));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicAccountsGetSearchRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicAccountsGetSearchRequest* UBasicAccountsGetSearchRequest::Make(FString _Query, int32 _Page, int32 _Pagesize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicAccountsGetSearchRequest* Req = NewObject<UBasicAccountsGetSearchRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Query = _Query;
	Req->Page = _Page;
	Req->Pagesize = _Pagesize;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
