
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostLogsUrlRequest.h"

void UPostLogsUrlRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostLogsUrlRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/logsUrl");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostLogsUrlRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostLogsUrlRequest* UPostLogsUrlRequest::Make(FString _ServiceName, FOptionalInt64 _StartTime, FOptionalString _NextToken, FOptionalString _Filter, FOptionalInt64 _EndTime, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostLogsUrlRequest* Req = NewObject<UPostLogsUrlRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetLogsUrlRequestBody>(Req);
	Req->Body->ServiceName = _ServiceName;
	Req->Body->StartTime = _StartTime;
	Req->Body->NextToken = _NextToken;
	Req->Body->Filter = _Filter;
	Req->Body->EndTime = _EndTime;
	Req->Body->Limit = _Limit;
	

	return Req;
}
