
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetTemplatesRequest.h"

void UGetTemplatesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetTemplatesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/templates");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetTemplatesRequest::BuildBody(FString& BodyString) const
{
	
}

UGetTemplatesRequest* UGetTemplatesRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetTemplatesRequest* Req = NewObject<UGetTemplatesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
