
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/DiscordSampleMs/DiscordSampleMsUpdateUserWhitelistedStatusRequest.h"

void UDiscordSampleMsUpdateUserWhitelistedStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UDiscordSampleMsUpdateUserWhitelistedStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_DiscordSampleMs/UpdateUserWhitelistedStatus");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDiscordSampleMsUpdateUserWhitelistedStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UDiscordSampleMsUpdateUserWhitelistedStatusRequest* UDiscordSampleMsUpdateUserWhitelistedStatusRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDiscordSampleMsUpdateUserWhitelistedStatusRequest* Req = NewObject<UDiscordSampleMsUpdateUserWhitelistedStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
