
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsProcessMatchResultRequest.h"

void UBeamballMsProcessMatchResultRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamballMsProcessMatchResultRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamballMs/ProcessMatchResult");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamballMsProcessMatchResultRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamballMsProcessMatchResultRequest* UBeamballMsProcessMatchResultRequest::Make(FString _WinnerId, FString _LobbyId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamballMsProcessMatchResultRequest* Req = NewObject<UBeamballMsProcessMatchResultRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UProcessMatchResultRequestArgs>(Req);
	Req->Body->WinnerId = _WinnerId;
	Req->Body->LobbyId = _LobbyId;
	

	return Req;
}
