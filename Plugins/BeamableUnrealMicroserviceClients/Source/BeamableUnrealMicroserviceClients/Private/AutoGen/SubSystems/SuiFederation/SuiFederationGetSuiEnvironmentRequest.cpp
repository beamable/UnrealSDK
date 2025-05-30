
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/SuiFederation/SuiFederationGetSuiEnvironmentRequest.h"

void USuiFederationGetSuiEnvironmentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void USuiFederationGetSuiEnvironmentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_SuiFederation/GetSuiEnvironment");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void USuiFederationGetSuiEnvironmentRequest::BuildBody(FString& BodyString) const
{
	
}

USuiFederationGetSuiEnvironmentRequest* USuiFederationGetSuiEnvironmentRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	USuiFederationGetSuiEnvironmentRequest* Req = NewObject<USuiFederationGetSuiEnvironmentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
