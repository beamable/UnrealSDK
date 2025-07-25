
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesFederationRequest.h"

void UPostServicesFederationRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostServicesFederationRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/federation");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostServicesFederationRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostServicesFederationRequest* UPostServicesFederationRequest::Make(FOptionalBool _bLocalOnly, FOptionalString _ServiceName, FOptionalString _RoutingKey, FOptionalBeamoV2SupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostServicesFederationRequest* Req = NewObject<UPostServicesFederationRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2ServiceRegistrationQuery>(Req);
	Req->Body->bLocalOnly = _bLocalOnly;
	Req->Body->ServiceName = _ServiceName;
	Req->Body->RoutingKey = _RoutingKey;
	Req->Body->Federation = _Federation;
	

	return Req;
}
