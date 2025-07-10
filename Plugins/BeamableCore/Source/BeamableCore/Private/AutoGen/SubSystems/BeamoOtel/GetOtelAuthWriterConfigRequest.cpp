
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/GetOtelAuthWriterConfigRequest.h"

void UGetOtelAuthWriterConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetOtelAuthWriterConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/otel/auth/writer/config");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetOtelAuthWriterConfigRequest::BuildBody(FString& BodyString) const
{
	
}

UGetOtelAuthWriterConfigRequest* UGetOtelAuthWriterConfigRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetOtelAuthWriterConfigRequest* Req = NewObject<UGetOtelAuthWriterConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
