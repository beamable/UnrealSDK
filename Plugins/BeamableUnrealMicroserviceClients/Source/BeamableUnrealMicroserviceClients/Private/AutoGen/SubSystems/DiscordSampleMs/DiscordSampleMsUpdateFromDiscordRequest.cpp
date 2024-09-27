
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/DiscordSampleMs/DiscordSampleMsUpdateFromDiscordRequest.h"

void UDiscordSampleMsUpdateFromDiscordRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UDiscordSampleMsUpdateFromDiscordRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_DiscordSampleMs/UpdateFromDiscord");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDiscordSampleMsUpdateFromDiscordRequest::BuildBody(FString& BodyString) const
{
	
}

UDiscordSampleMsUpdateFromDiscordRequest* UDiscordSampleMsUpdateFromDiscordRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDiscordSampleMsUpdateFromDiscordRequest* Req = NewObject<UDiscordSampleMsUpdateFromDiscordRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
