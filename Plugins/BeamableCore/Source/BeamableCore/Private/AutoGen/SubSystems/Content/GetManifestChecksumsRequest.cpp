
#include "AutoGen/SubSystems/Content/GetManifestChecksumsRequest.h"

void UGetManifestChecksumsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetManifestChecksumsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifest/checksums");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetManifestChecksumsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetManifestChecksumsRequest* UGetManifestChecksumsRequest::Make(UObject* RequestOwner)
{
	UGetManifestChecksumsRequest* Req = NewObject<UGetManifestChecksumsRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
