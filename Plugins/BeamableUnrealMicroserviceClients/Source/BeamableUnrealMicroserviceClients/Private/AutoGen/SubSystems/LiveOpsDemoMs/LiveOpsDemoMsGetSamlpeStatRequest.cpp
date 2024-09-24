
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsGetSamlpeStatRequest.h"

void ULiveOpsDemoMsGetSamlpeStatRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMsGetSamlpeStatRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("_microLiveOpsDemoMs/GetSamlpeStat");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMsGetSamlpeStatRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMsGetSamlpeStatRequest* ULiveOpsDemoMsGetSamlpeStatRequest::Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMsGetSamlpeStatRequest* Req = NewObject<ULiveOpsDemoMsGetSamlpeStatRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetSamlpeStatRequestArgs>(Req);
	Req->Body->UserID = _UserID;
	

	return Req;
}
