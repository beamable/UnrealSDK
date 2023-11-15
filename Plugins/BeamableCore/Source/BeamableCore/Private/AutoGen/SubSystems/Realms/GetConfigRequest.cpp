
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetConfigRequest.h"

void UGetConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/config");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetConfigRequest::BuildBody(FString& BodyString) const
{
	
}

UGetConfigRequest* UGetConfigRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetConfigRequest* Req = NewObject<UGetConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
