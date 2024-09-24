
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsIncrementStatRequest.h"

void ULiveOpsDemoMsIncrementStatRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMsIncrementStatRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("_microLiveOpsDemoMs/IncrementStat");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMsIncrementStatRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMsIncrementStatRequest* ULiveOpsDemoMsIncrementStatRequest::Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMsIncrementStatRequest* Req = NewObject<ULiveOpsDemoMsIncrementStatRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UIncrementStatRequestArgs>(Req);
	Req->Body->UserID = _UserID;
	

	return Req;
}
