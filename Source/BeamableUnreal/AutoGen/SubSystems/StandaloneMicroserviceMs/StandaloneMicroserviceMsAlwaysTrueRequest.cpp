
#include "BeamableUnreal/AutoGen/SubSystems/StandaloneMicroserviceMs/StandaloneMicroserviceMsAlwaysTrueRequest.h"

void UStandaloneMicroserviceMsAlwaysTrueRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UStandaloneMicroserviceMsAlwaysTrueRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_standalone_microservice/AlwaysTrue");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UStandaloneMicroserviceMsAlwaysTrueRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UStandaloneMicroserviceMsAlwaysTrueRequest* UStandaloneMicroserviceMsAlwaysTrueRequest::Make(FString _Text, UObject* RequestOwner)
{
	UStandaloneMicroserviceMsAlwaysTrueRequest* Req = NewObject<UStandaloneMicroserviceMsAlwaysTrueRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStandaloneMicroserviceAlwaysTrueRequestArgs>(Req);
	Req->Body->Text = _Text;
	

	return Req;
}
