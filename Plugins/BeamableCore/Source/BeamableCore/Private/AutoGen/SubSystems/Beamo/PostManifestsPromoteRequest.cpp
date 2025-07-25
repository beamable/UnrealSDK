
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestsPromoteRequest.h"

void UPostManifestsPromoteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostManifestsPromoteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/manifests/promote");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostManifestsPromoteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostManifestsPromoteRequest* UPostManifestsPromoteRequest::Make(FString _SourceRealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostManifestsPromoteRequest* Req = NewObject<UPostManifestsPromoteRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2PromoteBeamoManifestRequestBody>(Req);
	Req->Body->SourceRealmId = _SourceRealmId;
	

	return Req;
}
