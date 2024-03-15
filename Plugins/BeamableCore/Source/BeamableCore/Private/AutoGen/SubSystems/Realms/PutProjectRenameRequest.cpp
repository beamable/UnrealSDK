
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutProjectRenameRequest.h"

void UPutProjectRenameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutProjectRenameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project/rename");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutProjectRenameRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutProjectRenameRequest* UPutProjectRenameRequest::Make(FBeamPid _ProjectId, FString _NewName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutProjectRenameRequest* Req = NewObject<UPutProjectRenameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URenameProjectRequestBody>(Req);
	Req->Body->ProjectId = _ProjectId;
	Req->Body->NewName = _NewName;
	

	return Req;
}
