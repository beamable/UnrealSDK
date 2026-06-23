
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsUpdateUserWhitelistedStatusRequest.h"

void UBeamballMsUpdateUserWhitelistedStatusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamballMsUpdateUserWhitelistedStatusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamballMs/UpdateUserWhitelistedStatus");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamballMsUpdateUserWhitelistedStatusRequest::BuildBody(FString& BodyString) const
{
	
}

UBeamballMsUpdateUserWhitelistedStatusRequest* UBeamballMsUpdateUserWhitelistedStatusRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamballMsUpdateUserWhitelistedStatusRequest* Req = NewObject<UBeamballMsUpdateUserWhitelistedStatusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
