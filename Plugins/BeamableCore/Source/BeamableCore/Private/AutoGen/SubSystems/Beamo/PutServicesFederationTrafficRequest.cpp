
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutServicesFederationTrafficRequest.h"

void UPutServicesFederationTrafficRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutServicesFederationTrafficRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/{serviceName}/federation/traffic");
	Route = Route.Replace(TEXT("{serviceName}"), *ServiceName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutServicesFederationTrafficRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutServicesFederationTrafficRequest* UPutServicesFederationTrafficRequest::Make(FString _ServiceName, FOptionalString _RoutingKey, FOptionalBool _bTrafficFilterEnabled, FOptionalArrayOfBeamoV2SupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutServicesFederationTrafficRequest* Req = NewObject<UPutServicesFederationTrafficRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2ServiceRegistrationRequestBody>(Req);
	Req->Body->RoutingKey = _RoutingKey;
	Req->Body->bTrafficFilterEnabled = _bTrafficFilterEnabled;
	Req->Body->Federation = _Federation;
	

	return Req;
}
