
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/DeleteAdminInflightFailuresRequest.h"

void UDeleteAdminInflightFailuresRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteAdminInflightFailuresRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/admin/inflight/failures");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteAdminInflightFailuresRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteAdminInflightFailuresRequest* UDeleteAdminInflightFailuresRequest::Make(TArray<FString> _InFlightFailureIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteAdminInflightFailuresRequest* Req = NewObject<UDeleteAdminInflightFailuresRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBatchDeleteInFlightRequestBody>(Req);
	Req->Body->InFlightFailureIds = _InFlightFailureIds;
	

	return Req;
}
