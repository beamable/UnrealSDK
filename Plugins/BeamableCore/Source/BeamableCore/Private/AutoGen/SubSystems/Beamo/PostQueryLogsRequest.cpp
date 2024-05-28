
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostQueryLogsRequest.h"

void UPostQueryLogsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostQueryLogsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/queryLogs");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostQueryLogsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostQueryLogsRequest* UPostQueryLogsRequest::Make(FString _ServiceName, FOptionalInt64 _StartTime, FOptionalString _Filter, FOptionalInt64 _EndTime, FOptionalString _Order, FOptionalInt32 _Limit, FOptionalArrayOfString _Filters, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostQueryLogsRequest* Req = NewObject<UPostQueryLogsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetLogsInsightUrlRequestBody>(Req);
	Req->Body->ServiceName = _ServiceName;
	Req->Body->StartTime = _StartTime;
	Req->Body->Filter = _Filter;
	Req->Body->EndTime = _EndTime;
	Req->Body->Order = _Order;
	Req->Body->Limit = _Limit;
	Req->Body->Filters = _Filters;
	

	return Req;
}
