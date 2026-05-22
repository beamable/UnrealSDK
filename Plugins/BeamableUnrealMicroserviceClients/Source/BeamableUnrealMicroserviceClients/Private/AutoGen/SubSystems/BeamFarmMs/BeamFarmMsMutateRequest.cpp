
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsMutateRequest.h"

void UBeamFarmMsMutateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsMutateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/Mutate");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsMutateRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsMutateRequest* UBeamFarmMsMutateRequest::Make(TArray<UMutationInput*> _Inputs, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsMutateRequest* Req = NewObject<UBeamFarmMsMutateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMutateRequestArgs>(Req);
	Req->Body->Inputs = _Inputs;
	

	return Req;
}
