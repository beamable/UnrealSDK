
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLFromPortalRequest.h"

void UPostDataDownloadURLFromPortalRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostDataDownloadURLFromPortalRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/downloadURLFromPortal");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostDataDownloadURLFromPortalRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostDataDownloadURLFromPortalRequest* UPostDataDownloadURLFromPortalRequest::Make(FOptionalInt64 _PlayerId, FOptionalArrayOfObjectRequestBody _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostDataDownloadURLFromPortalRequest* Req = NewObject<UPostDataDownloadURLFromPortalRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UObjectRequests>(Req);
	Req->Body->PlayerId = _PlayerId;
	Req->Body->Request = _Request;
	

	return Req;
}
