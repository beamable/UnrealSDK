
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSGetSamlpeStatRequest.h"

void ULiveOpsDemoMSGetSamlpeStatRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMSGetSamlpeStatRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_LiveOpsDemoMS/GetSamlpeStat");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMSGetSamlpeStatRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMSGetSamlpeStatRequest* ULiveOpsDemoMSGetSamlpeStatRequest::Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMSGetSamlpeStatRequest* Req = NewObject<ULiveOpsDemoMSGetSamlpeStatRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetSamlpeStatRequestArgs>(Req);
	Req->Body->UserID = _UserID;
	

	return Req;
}
