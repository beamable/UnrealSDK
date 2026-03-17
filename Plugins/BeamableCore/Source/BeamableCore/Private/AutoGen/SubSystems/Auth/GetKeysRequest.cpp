
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetKeysRequest.h"

void UGetKeysRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetKeysRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/keys");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetKeysRequest::BuildBody(FString& BodyString) const
{
	
}

UGetKeysRequest* UGetKeysRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetKeysRequest* Req = NewObject<UGetKeysRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
