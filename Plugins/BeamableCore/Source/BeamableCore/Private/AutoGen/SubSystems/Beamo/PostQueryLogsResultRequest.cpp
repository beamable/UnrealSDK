
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostQueryLogsResultRequest.h"

void UPostQueryLogsResultRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostQueryLogsResultRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/queryLogs/result");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostQueryLogsResultRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostQueryLogsResultRequest* UPostQueryLogsResultRequest::Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostQueryLogsResultRequest* Req = NewObject<UPostQueryLogsResultRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UQuery>(Req);
	Req->Body->QueryId = _QueryId;
	

	return Req;
}
