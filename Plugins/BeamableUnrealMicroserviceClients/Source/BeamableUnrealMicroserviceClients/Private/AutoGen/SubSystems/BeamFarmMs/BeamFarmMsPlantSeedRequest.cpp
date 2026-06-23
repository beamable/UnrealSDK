
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsPlantSeedRequest.h"

void UBeamFarmMsPlantSeedRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsPlantSeedRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/PlantSeed");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsPlantSeedRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsPlantSeedRequest* UBeamFarmMsPlantSeedRequest::Make(FString _SeedContentId, FString _SlotId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsPlantSeedRequest* Req = NewObject<UBeamFarmMsPlantSeedRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPlantSeedRequestArgs>(Req);
	Req->Body->SeedContentId = _SeedContentId;
	Req->Body->SlotId = _SlotId;
	

	return Req;
}
