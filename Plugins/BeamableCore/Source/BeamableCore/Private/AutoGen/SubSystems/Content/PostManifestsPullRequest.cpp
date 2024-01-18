
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostManifestsPullRequest.h"

void UPostManifestsPullRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestsPullRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifests/pull");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestsPullRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestsPullRequest* UPostManifestsPullRequest::Make(FBeamPid _SourceRealmPid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostManifestsPullRequest* Req = NewObject<UPostManifestsPullRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPullAllManifestsRequestBody>(Req);
	Req->Body->SourceRealmPid = _SourceRealmPid;
	

	return Req;
}
