
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableRequest.h"

void UGetAvailableRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/available");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("email"), *Email);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailableRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableRequest* UGetAvailableRequest::Make(FString _Email, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAvailableRequest* Req = NewObject<UGetAvailableRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Email = _Email;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
