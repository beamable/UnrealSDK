
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetSlotStatesRequest.h"

void UBeamFarmMsGetSlotStatesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsGetSlotStatesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/GetSlotStates");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsGetSlotStatesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsGetSlotStatesRequest* UBeamFarmMsGetSlotStatesRequest::Make(TArray<FString> _SlotIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsGetSlotStatesRequest* Req = NewObject<UBeamFarmMsGetSlotStatesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetSlotStatesRequestArgs>(Req);
	Req->Body->SlotIds = _SlotIds;
	

	return Req;
}
