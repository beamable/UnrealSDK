
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsUpdateFromDiscordRequest.h"

void UBeamballMsUpdateFromDiscordRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamballMsUpdateFromDiscordRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamballMs/UpdateFromDiscord");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamballMsUpdateFromDiscordRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamballMsUpdateFromDiscordRequest* UBeamballMsUpdateFromDiscordRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamballMsUpdateFromDiscordRequest* Req = NewObject<UBeamballMsUpdateFromDiscordRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
