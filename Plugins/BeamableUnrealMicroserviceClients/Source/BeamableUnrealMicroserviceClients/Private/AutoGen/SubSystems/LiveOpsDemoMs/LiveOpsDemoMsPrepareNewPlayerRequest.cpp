
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsPrepareNewPlayerRequest.h"

void ULiveOpsDemoMsPrepareNewPlayerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMsPrepareNewPlayerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("_microLiveOpsDemoMs/PrepareNewPlayer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMsPrepareNewPlayerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMsPrepareNewPlayerRequest* ULiveOpsDemoMsPrepareNewPlayerRequest::Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMsPrepareNewPlayerRequest* Req = NewObject<ULiveOpsDemoMsPrepareNewPlayerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPrepareNewPlayerRequestArgs>(Req);
	Req->Body->UserID = _UserID;
	

	return Req;
}
