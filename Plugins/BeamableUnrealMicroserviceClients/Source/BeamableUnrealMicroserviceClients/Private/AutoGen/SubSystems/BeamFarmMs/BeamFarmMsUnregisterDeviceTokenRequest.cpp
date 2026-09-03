
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsUnregisterDeviceTokenRequest.h"

void UBeamFarmMsUnregisterDeviceTokenRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsUnregisterDeviceTokenRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/UnregisterDeviceToken");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsUnregisterDeviceTokenRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsUnregisterDeviceTokenRequest* UBeamFarmMsUnregisterDeviceTokenRequest::Make(FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsUnregisterDeviceTokenRequest* Req = NewObject<UBeamFarmMsUnregisterDeviceTokenRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUnregisterDeviceTokenRequestArgs>(Req);
	Req->Body->Token = _Token;
	

	return Req;
}
