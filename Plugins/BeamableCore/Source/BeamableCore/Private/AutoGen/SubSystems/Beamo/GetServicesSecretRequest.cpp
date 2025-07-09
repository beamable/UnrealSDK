
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetServicesSecretRequest.h"

void UGetServicesSecretRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetServicesSecretRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/secret");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetServicesSecretRequest::BuildBody(FString& BodyString) const
{
	
}

UGetServicesSecretRequest* UGetServicesSecretRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetServicesSecretRequest* Req = NewObject<UGetServicesSecretRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
