
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSPrepareNewPlayerRequest.h"

void ULiveOpsDemoMSPrepareNewPlayerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMSPrepareNewPlayerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_LiveOpsDemoMS/PrepareNewPlayer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMSPrepareNewPlayerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMSPrepareNewPlayerRequest* ULiveOpsDemoMSPrepareNewPlayerRequest::Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMSPrepareNewPlayerRequest* Req = NewObject<ULiveOpsDemoMSPrepareNewPlayerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPrepareNewPlayerRequestArgs>(Req);
	Req->Body->UserID = _UserID;
	

	return Req;
}
