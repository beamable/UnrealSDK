
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutGameRequest.h"

void UPutGameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutGameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/game");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutGameRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutGameRequest* UPutGameRequest::Make(FBeamPid _RootPID, TArray<UProjectView*> _Projects, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutGameRequest* Req = NewObject<UPutGameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateGameHierarchyRequestBody>(Req);
	Req->Body->RootPID = _RootPID;
	Req->Body->Projects = _Projects;
	

	return Req;
}
