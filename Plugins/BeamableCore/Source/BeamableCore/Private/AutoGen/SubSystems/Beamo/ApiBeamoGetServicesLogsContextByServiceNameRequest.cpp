
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetServicesLogsContextByServiceNameRequest.h"

void UApiBeamoGetServicesLogsContextByServiceNameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetServicesLogsContextByServiceNameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/{serviceName}/logs/context");
	Route = Route.Replace(TEXT("{serviceName}"), *ServiceName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(RoutingKey.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("routingKey"), *RoutingKey.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetServicesLogsContextByServiceNameRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetServicesLogsContextByServiceNameRequest* UApiBeamoGetServicesLogsContextByServiceNameRequest::Make(FString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetServicesLogsContextByServiceNameRequest* Req = NewObject<UApiBeamoGetServicesLogsContextByServiceNameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	Req->RoutingKey = _RoutingKey;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
