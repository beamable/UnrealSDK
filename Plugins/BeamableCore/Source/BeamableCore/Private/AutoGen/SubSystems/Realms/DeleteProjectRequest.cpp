
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/DeleteProjectRequest.h"

void UDeleteProjectRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteProjectRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteProjectRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteProjectRequest* UDeleteProjectRequest::Make(FBeamPid _Pid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteProjectRequest* Req = NewObject<UDeleteProjectRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UArchiveProjectRequestBody>(Req);
	Req->Body->Pid = _Pid;
	

	return Req;
}
