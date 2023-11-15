
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetLocalizationsRequest.h"

void UGetLocalizationsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetLocalizationsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/localizations");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetLocalizationsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetLocalizationsRequest* UGetLocalizationsRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetLocalizationsRequest* Req = NewObject<UGetLocalizationsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
