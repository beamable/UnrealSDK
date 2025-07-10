
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetRegistryUriRequest.h"

void UGetRegistryUriRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRegistryUriRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/registry-uri");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRegistryUriRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRegistryUriRequest* UGetRegistryUriRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRegistryUriRequest* Req = NewObject<UGetRegistryUriRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
