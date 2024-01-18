
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PutDataMoveRequest.h"

void UPutDataMoveRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutDataMoveRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/move");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutDataMoveRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutDataMoveRequest* UPutDataMoveRequest::Make(FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutDataMoveRequest* Req = NewObject<UPutDataMoveRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPlayerBasicCloudDataRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
