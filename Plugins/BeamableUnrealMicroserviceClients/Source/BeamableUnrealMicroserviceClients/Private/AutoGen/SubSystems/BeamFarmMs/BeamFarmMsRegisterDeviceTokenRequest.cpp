
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsRegisterDeviceTokenRequest.h"

void UBeamFarmMsRegisterDeviceTokenRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsRegisterDeviceTokenRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/RegisterDeviceToken");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsRegisterDeviceTokenRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsRegisterDeviceTokenRequest* UBeamFarmMsRegisterDeviceTokenRequest::Make(FString _Token, FString _Environment, FString _Platform, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsRegisterDeviceTokenRequest* Req = NewObject<UBeamFarmMsRegisterDeviceTokenRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URegisterDeviceTokenRequestArgs>(Req);
	Req->Body->Token = _Token;
	Req->Body->Environment = _Environment;
	Req->Body->Platform = _Platform;
	

	return Req;
}
