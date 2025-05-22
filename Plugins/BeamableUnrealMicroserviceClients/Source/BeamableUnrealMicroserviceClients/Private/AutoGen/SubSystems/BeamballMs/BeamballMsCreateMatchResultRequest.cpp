
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsCreateMatchResultRequest.h"

void UBeamballMsCreateMatchResultRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamballMsCreateMatchResultRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamballMs/CreateMatchResult");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamballMsCreateMatchResultRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamballMsCreateMatchResultRequest* UBeamballMsCreateMatchResultRequest::Make(FString _LobbyId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamballMsCreateMatchResultRequest* Req = NewObject<UBeamballMsCreateMatchResultRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateMatchResultRequestArgs>(Req);
	Req->Body->LobbyId = _LobbyId;
	

	return Req;
}
