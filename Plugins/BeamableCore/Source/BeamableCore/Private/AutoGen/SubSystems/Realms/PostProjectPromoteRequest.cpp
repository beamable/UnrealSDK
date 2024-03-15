
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostProjectPromoteRequest.h"

void UPostProjectPromoteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostProjectPromoteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project/promote");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostProjectPromoteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostProjectPromoteRequest* UPostProjectPromoteRequest::Make(FBeamPid _SourcePid, FOptionalArrayOfString _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostProjectPromoteRequest* Req = NewObject<UPostProjectPromoteRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPromoteRealmRequestBody>(Req);
	Req->Body->SourcePid = _SourcePid;
	Req->Body->Promotions = _Promotions;
	Req->Body->ContentManifestIds = _ContentManifestIds;
	

	return Req;
}
