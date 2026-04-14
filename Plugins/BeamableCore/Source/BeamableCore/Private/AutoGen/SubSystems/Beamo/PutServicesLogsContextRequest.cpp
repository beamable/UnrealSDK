
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutServicesLogsContextRequest.h"

void UPutServicesLogsContextRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutServicesLogsContextRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/{serviceName}/logs/context");
	Route = Route.Replace(TEXT("{serviceName}"), *ServiceName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutServicesLogsContextRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutServicesLogsContextRequest* UPutServicesLogsContextRequest::Make(FString _ServiceName, FString Body_ServiceName, FString _RoutingKey, EBeamBeamoV2LogLevel _DefaultLogLevel, FOptionalString _Id, FOptionalArrayOfBeamoV2LogContextRule _Rules, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutServicesLogsContextRequest* Req = NewObject<UPutServicesLogsContextRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2ServiceLoggingContext>(Req);
	Req->Body->ServiceName = Body_ServiceName;
	Req->Body->RoutingKey = _RoutingKey;
	Req->Body->DefaultLogLevel = _DefaultLogLevel;
	Req->Body->Id = _Id;
	Req->Body->Rules = _Rules;
	

	return Req;
}
