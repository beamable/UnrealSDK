
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsMutateWithModifiersRequest.h"

void UBeamFarmMsMutateWithModifiersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsMutateWithModifiersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/MutateWithModifiers");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsMutateWithModifiersRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsMutateWithModifiersRequest* UBeamFarmMsMutateWithModifiersRequest::Make(FString _PlantItemContentId, int64 _PlantItemInstanceId, TArray<FString> _ModifierContentIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsMutateWithModifiersRequest* Req = NewObject<UBeamFarmMsMutateWithModifiersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMutateWithModifiersRequestArgs>(Req);
	Req->Body->PlantItemContentId = _PlantItemContentId;
	Req->Body->PlantItemInstanceId = _PlantItemInstanceId;
	Req->Body->ModifierContentIds = _ModifierContentIds;
	

	return Req;
}
