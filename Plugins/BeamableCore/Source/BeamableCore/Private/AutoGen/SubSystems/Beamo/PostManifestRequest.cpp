
#include "AutoGen/SubSystems/Beamo/PostManifestRequest.h"

void UPostManifestRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/manifest");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestRequest* UPostManifestRequest::Make(TArray<UServiceReference*> _Manifest, FOptionalBool _bAutoDeploy, FOptionalString _Comments, FOptionalArrayOfServiceStorageReference _StorageReferences, UObject* Outer)
{
	UPostManifestRequest* Req = NewObject<UPostManifestRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPostManifestRequestBody>(Req);
	Req->Body->Manifest = _Manifest;
	Req->Body->bAutoDeploy = _bAutoDeploy;
	Req->Body->Comments = _Comments;
	Req->Body->StorageReferences = _StorageReferences;
	

	return Req;
}
