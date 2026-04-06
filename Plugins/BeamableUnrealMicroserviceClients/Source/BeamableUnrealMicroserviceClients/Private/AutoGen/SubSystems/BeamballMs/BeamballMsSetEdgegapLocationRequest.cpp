
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsSetEdgegapLocationRequest.h"

void UBeamballMsSetEdgegapLocationRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamballMsSetEdgegapLocationRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamballMs/SetEdgegapLocation");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamballMsSetEdgegapLocationRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamballMsSetEdgegapLocationRequest* UBeamballMsSetEdgegapLocationRequest::Make(float _Latitude, float _Longitude, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamballMsSetEdgegapLocationRequest* Req = NewObject<UBeamballMsSetEdgegapLocationRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USetEdgegapLocationRequestArgs>(Req);
	Req->Body->Latitude = _Latitude;
	Req->Body->Longitude = _Longitude;
	

	return Req;
}
