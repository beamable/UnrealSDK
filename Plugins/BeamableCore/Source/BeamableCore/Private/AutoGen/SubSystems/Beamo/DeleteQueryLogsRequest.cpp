
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteQueryLogsRequest.h"

void UDeleteQueryLogsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteQueryLogsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/queryLogs");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteQueryLogsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteQueryLogsRequest* UDeleteQueryLogsRequest::Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteQueryLogsRequest* Req = NewObject<UDeleteQueryLogsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UQuery>(Req);
	Req->Body->QueryId = _QueryId;
	

	return Req;
}
