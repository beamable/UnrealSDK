
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestExactRequest.h"

void UGetManifestExactRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetManifestExactRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifest/exact");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("uid"), *Uid);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetManifestExactRequest::BuildBody(FString& BodyString) const
{
	
}

UGetManifestExactRequest* UGetManifestExactRequest::Make(FString _Uid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetManifestExactRequest* Req = NewObject<UGetManifestExactRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Uid = _Uid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
