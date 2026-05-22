
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsRegisterGroundItemRequest.h"

void UBeamFarmMsRegisterGroundItemRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsRegisterGroundItemRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/RegisterGroundItem");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsRegisterGroundItemRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsRegisterGroundItemRequest* UBeamFarmMsRegisterGroundItemRequest::Make(FString _GroundItemId, FString _ContentId, int32 _Quantity, FString _ItemType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsRegisterGroundItemRequest* Req = NewObject<UBeamFarmMsRegisterGroundItemRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URegisterGroundItemRequestArgs>(Req);
	Req->Body->GroundItemId = _GroundItemId;
	Req->Body->ContentId = _ContentId;
	Req->Body->Quantity = _Quantity;
	Req->Body->ItemType = _ItemType;
	

	return Req;
}
