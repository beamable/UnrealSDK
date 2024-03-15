
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostBatchRequest.h"

void UPostBatchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostBatchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/stats/batch");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostBatchRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostBatchRequest* UPostBatchRequest::Make(TArray<UStatUpdateRequestBody*> _Updates, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostBatchRequest* Req = NewObject<UPostBatchRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBatchSetStatsRequestBody>(Req);
	Req->Body->Updates = _Updates;
	

	return Req;
}
