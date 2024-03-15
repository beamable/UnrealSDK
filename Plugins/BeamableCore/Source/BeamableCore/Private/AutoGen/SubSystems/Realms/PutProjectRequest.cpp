
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutProjectRequest.h"

void UPutProjectRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutProjectRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutProjectRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutProjectRequest* UPutProjectRequest::Make(FBeamPid _ProjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutProjectRequest* Req = NewObject<UPutProjectRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUnarchiveProjectRequestBody>(Req);
	Req->Body->ProjectId = _ProjectId;
	

	return Req;
}
