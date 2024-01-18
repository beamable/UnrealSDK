
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostManifestsUnarchiveRequest.h"

void UPostManifestsUnarchiveRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestsUnarchiveRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifests/unarchive");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestsUnarchiveRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestsUnarchiveRequest* UPostManifestsUnarchiveRequest::Make(TArray<FBeamContentManifestId> _ManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostManifestsUnarchiveRequest* Req = NewObject<UPostManifestsUnarchiveRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UArchiveOrUnarchiveManifestsRequestBody>(Req);
	Req->Body->ManifestIds = _ManifestIds;
	

	return Req;
}
