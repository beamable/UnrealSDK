
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestsRequest.h"

void UPostManifestsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/manifests");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestsRequest* UPostManifestsRequest::Make(FOptionalBool _bAutoDeploy, FOptionalString _Comments, FOptionalArrayOfBeamoV2ServiceReference _Manifest, FOptionalArrayOfBeamoV2ServiceStorageReference _StorageReferences, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostManifestsRequest* Req = NewObject<UPostManifestsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2PostManifestRequestBody>(Req);
	Req->Body->bAutoDeploy = _bAutoDeploy;
	Req->Body->Comments = _Comments;
	Req->Body->Manifest = _Manifest;
	Req->Body->StorageReferences = _StorageReferences;
	

	return Req;
}
