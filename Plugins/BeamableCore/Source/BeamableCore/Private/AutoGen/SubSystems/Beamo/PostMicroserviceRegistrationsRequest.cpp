
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostMicroserviceRegistrationsRequest.h"

void UPostMicroserviceRegistrationsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostMicroserviceRegistrationsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/microservice/registrations");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostMicroserviceRegistrationsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostMicroserviceRegistrationsRequest* UPostMicroserviceRegistrationsRequest::Make(FOptionalBool _bLocalOnly, FOptionalString _ServiceName, FOptionalString _RoutingKey, FOptionalSupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostMicroserviceRegistrationsRequest* Req = NewObject<UPostMicroserviceRegistrationsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMicroserviceRegistrationsQuery>(Req);
	Req->Body->bLocalOnly = _bLocalOnly;
	Req->Body->ServiceName = _ServiceName;
	Req->Body->RoutingKey = _RoutingKey;
	Req->Body->Federation = _Federation;
	

	return Req;
}
