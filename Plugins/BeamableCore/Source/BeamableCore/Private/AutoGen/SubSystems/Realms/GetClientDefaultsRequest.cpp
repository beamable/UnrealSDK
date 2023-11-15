
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"

void UGetClientDefaultsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetClientDefaultsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/client/defaults");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetClientDefaultsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetClientDefaultsRequest* UGetClientDefaultsRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetClientDefaultsRequest* Req = NewObject<UGetClientDefaultsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
