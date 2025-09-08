
#include "BeamableCore/Public/AutoGen/SubSystems/Admin/DeleteInflightFailuresRequest.h"

void UDeleteInflightFailuresRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteInflightFailuresRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/admin/inflight/failures");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteInflightFailuresRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteInflightFailuresRequest* UDeleteInflightFailuresRequest::Make(TArray<FString> _InFlightFailureIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteInflightFailuresRequest* Req = NewObject<UDeleteInflightFailuresRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBatchDeleteInFlightRequestBody>(Req);
	Req->Body->InFlightFailureIds = _InFlightFailureIds;
	

	return Req;
}
