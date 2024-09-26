
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/HathoraDemo/HathoraDemoInitializePlayerRequest.h"

void UHathoraDemoInitializePlayerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UHathoraDemoInitializePlayerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_HathoraDemo/InitializePlayer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UHathoraDemoInitializePlayerRequest::BuildBody(FString& BodyString) const
{
	
}

UHathoraDemoInitializePlayerRequest* UHathoraDemoInitializePlayerRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UHathoraDemoInitializePlayerRequest* Req = NewObject<UHathoraDemoInitializePlayerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
