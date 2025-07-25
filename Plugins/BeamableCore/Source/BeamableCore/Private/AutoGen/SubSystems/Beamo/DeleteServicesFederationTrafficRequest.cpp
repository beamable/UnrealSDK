
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteServicesFederationTrafficRequest.h"

void UDeleteServicesFederationTrafficRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteServicesFederationTrafficRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/{serviceName}/federation/traffic");
	Route = Route.Replace(TEXT("{serviceName}"), *ServiceName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteServicesFederationTrafficRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteServicesFederationTrafficRequest* UDeleteServicesFederationTrafficRequest::Make(FString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteServicesFederationTrafficRequest* Req = NewObject<UDeleteServicesFederationTrafficRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2DeleteRegistrationRequestBody>(Req);
	Req->Body->RoutingKey = _RoutingKey;
	

	return Req;
}
