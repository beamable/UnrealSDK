
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesMetricsRequestRequest.h"

void UPostServicesMetricsRequestRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostServicesMetricsRequestRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/{serviceName}/metrics-request");
	Route = Route.Replace(TEXT("{serviceName}"), *ServiceName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostServicesMetricsRequestRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostServicesMetricsRequestRequest* UPostServicesMetricsRequestRequest::Make(FString _ServiceName, FOptionalString _MetricName, FOptionalDateTime _StartTime, FOptionalDateTime _EndTime, FOptionalInt32 _Period, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostServicesMetricsRequestRequest* Req = NewObject<UPostServicesMetricsRequestRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2GetMetricsRequestBody>(Req);
	Req->Body->MetricName = _MetricName;
	Req->Body->StartTime = _StartTime;
	Req->Body->EndTime = _EndTime;
	Req->Body->Period = _Period;
	

	return Req;
}
