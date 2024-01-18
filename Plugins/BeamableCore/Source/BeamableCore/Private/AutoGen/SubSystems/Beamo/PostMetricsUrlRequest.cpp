
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostMetricsUrlRequest.h"

void UPostMetricsUrlRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostMetricsUrlRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/metricsUrl");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostMetricsUrlRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostMetricsUrlRequest* UPostMetricsUrlRequest::Make(FString _ServiceName, FString _MetricName, FOptionalInt64 _StartTime, FOptionalInt64 _EndTime, FOptionalInt32 _Period, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostMetricsUrlRequest* Req = NewObject<UPostMetricsUrlRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetMetricsUrlRequestBody>(Req);
	Req->Body->ServiceName = _ServiceName;
	Req->Body->MetricName = _MetricName;
	Req->Body->StartTime = _StartTime;
	Req->Body->EndTime = _EndTime;
	Req->Body->Period = _Period;
	

	return Req;
}
