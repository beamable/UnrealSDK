
#include "PostDataUploadURLFromPortalRequest.h"

void UPostDataUploadURLFromPortalRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostDataUploadURLFromPortalRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/uploadURLFromPortal");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostDataUploadURLFromPortalRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostDataUploadURLFromPortalRequest* UPostDataUploadURLFromPortalRequest::MakePostDataUploadURLFromPortalRequest(TArray<UUploadRequestFromPortal*> _Request, FOptionalInt64 _PlayerId, UObject* Outer)
{
	UPostDataUploadURLFromPortalRequest* Req = NewObject<UPostDataUploadURLFromPortalRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUploadRequestsFromPortal>(Req);
	Req->Body->Request = _Request;
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
