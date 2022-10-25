
#include "AutoGen/SubSystems/Beamo/PostManifestPullRequest.h"

void UPostManifestPullRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestPullRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/manifest/pull");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestPullRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestPullRequest* UPostManifestPullRequest::Make(FString _SourceRealmPid, UObject* Outer)
{
	UPostManifestPullRequest* Req = NewObject<UPostManifestPullRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPullBeamoManifestRequestBody>(Req);
	Req->Body->SourceRealmPid = _SourceRealmPid;
	

	return Req;
}
