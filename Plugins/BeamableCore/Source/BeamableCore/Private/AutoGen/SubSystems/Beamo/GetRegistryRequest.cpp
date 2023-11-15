
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetRegistryRequest.h"

void UGetRegistryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRegistryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/registry");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRegistryRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRegistryRequest* UGetRegistryRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRegistryRequest* Req = NewObject<UGetRegistryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
