
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentPostManifestRequest.h"

void UBasicContentPostManifestRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBasicContentPostManifestRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifest");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicContentPostManifestRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicContentPostManifestRequest* UBasicContentPostManifestRequest::Make(FBeamContentManifestId _Id, TArray<UReferenceSuperset*> _References, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicContentPostManifestRequest* Req = NewObject<UBasicContentPostManifestRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USaveManifestRequestBody>(Req);
	Req->Body->Id = _Id;
	Req->Body->References = _References;
	

	return Req;
}
