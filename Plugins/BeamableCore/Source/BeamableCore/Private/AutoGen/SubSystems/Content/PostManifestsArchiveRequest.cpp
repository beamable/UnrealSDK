
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostManifestsArchiveRequest.h"

void UPostManifestsArchiveRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestsArchiveRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifests/archive");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestsArchiveRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestsArchiveRequest* UPostManifestsArchiveRequest::Make(TArray<FBeamContentManifestId> _ManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostManifestsArchiveRequest* Req = NewObject<UPostManifestsArchiveRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UArchiveOrUnarchiveManifestsRequestBody>(Req);
	Req->Body->ManifestIds = _ManifestIds;
	

	return Req;
}
