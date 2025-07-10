
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/GetOtelAuthReaderConfigRequest.h"

void UGetOtelAuthReaderConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetOtelAuthReaderConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/otel/auth/reader/config");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetOtelAuthReaderConfigRequest::BuildBody(FString& BodyString) const
{
	
}

UGetOtelAuthReaderConfigRequest* UGetOtelAuthReaderConfigRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetOtelAuthReaderConfigRequest* Req = NewObject<UGetOtelAuthReaderConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
