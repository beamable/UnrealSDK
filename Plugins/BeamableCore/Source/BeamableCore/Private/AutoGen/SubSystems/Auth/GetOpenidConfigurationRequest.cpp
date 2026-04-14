
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetOpenidConfigurationRequest.h"

void UGetOpenidConfigurationRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetOpenidConfigurationRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/.well-known/openid-configuration");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetOpenidConfigurationRequest::BuildBody(FString& BodyString) const
{
	
}

UGetOpenidConfigurationRequest* UGetOpenidConfigurationRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetOpenidConfigurationRequest* Req = NewObject<UGetOpenidConfigurationRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
