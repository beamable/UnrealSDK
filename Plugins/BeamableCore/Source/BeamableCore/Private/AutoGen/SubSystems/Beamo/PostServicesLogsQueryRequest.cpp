
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesLogsQueryRequest.h"

void UPostServicesLogsQueryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostServicesLogsQueryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/{serviceName}/logs/query");
	Route = Route.Replace(TEXT("{serviceName}"), *ServiceName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostServicesLogsQueryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostServicesLogsQueryRequest* UPostServicesLogsQueryRequest::Make(FString _ServiceName, FOptionalString Body_ServiceName, FOptionalDateTime _StartTime, FOptionalDateTime _EndTime, FOptionalBeamoV2OrderDirection _Order, FOptionalInt32 _Limit, FOptionalArrayOfString _Filters, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostServicesLogsQueryRequest* Req = NewObject<UPostServicesLogsQueryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2StartServiceLogsRequestBody>(Req);
	Req->Body->ServiceName = Body_ServiceName;
	Req->Body->StartTime = _StartTime;
	Req->Body->EndTime = _EndTime;
	Req->Body->Order = _Order;
	Req->Body->Limit = _Limit;
	Req->Body->Filters = _Filters;
	

	return Req;
}
