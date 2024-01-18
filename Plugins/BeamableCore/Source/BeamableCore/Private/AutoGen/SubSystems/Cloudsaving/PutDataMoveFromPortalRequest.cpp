
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PutDataMoveFromPortalRequest.h"

void UPutDataMoveFromPortalRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutDataMoveFromPortalRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/moveFromPortal");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutDataMoveFromPortalRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutDataMoveFromPortalRequest* UPutDataMoveFromPortalRequest::Make(FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutDataMoveFromPortalRequest* Req = NewObject<UPutDataMoveFromPortalRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPlayerBasicCloudDataRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
