
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutMicroserviceFederationTrafficRequest.h"

void UPutMicroserviceFederationTrafficRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutMicroserviceFederationTrafficRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/microservice/federation/traffic");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutMicroserviceFederationTrafficRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutMicroserviceFederationTrafficRequest* UPutMicroserviceFederationTrafficRequest::Make(FString _ServiceName, FOptionalBool _bTrafficFilterEnabled, FOptionalString _RoutingKey, FOptionalArrayOfSupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutMicroserviceFederationTrafficRequest* Req = NewObject<UPutMicroserviceFederationTrafficRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMicroserviceRegistrationRequestBody>(Req);
	Req->Body->ServiceName = _ServiceName;
	Req->Body->bTrafficFilterEnabled = _bTrafficFilterEnabled;
	Req->Body->RoutingKey = _RoutingKey;
	Req->Body->Federation = _Federation;
	

	return Req;
}
