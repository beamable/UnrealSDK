
#include "BeamableUnreal/AutoGen/SubSystems/StandaloneMicroserviceMs/StandaloneMicroserviceMsJoinNumbersAsStringRequest.h"

void UStandaloneMicroserviceMsJoinNumbersAsStringRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UStandaloneMicroserviceMsJoinNumbersAsStringRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_standalone_microservice/JoinNumbersAsString");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UStandaloneMicroserviceMsJoinNumbersAsStringRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UStandaloneMicroserviceMsJoinNumbersAsStringRequest* UStandaloneMicroserviceMsJoinNumbersAsStringRequest::Make(int32 _A, int32 _B, UObject* RequestOwner)
{
	UStandaloneMicroserviceMsJoinNumbersAsStringRequest* Req = NewObject<UStandaloneMicroserviceMsJoinNumbersAsStringRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStandaloneMicroserviceJoinNumbersAsStringRequestArgs>(Req);
	Req->Body->A = _A;
	Req->Body->B = _B;
	

	return Req;
}
