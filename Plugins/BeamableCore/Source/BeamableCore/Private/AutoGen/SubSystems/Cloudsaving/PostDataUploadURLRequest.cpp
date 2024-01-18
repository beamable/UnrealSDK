
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataUploadURLRequest.h"

void UPostDataUploadURLRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostDataUploadURLRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/uploadURL");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostDataUploadURLRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostDataUploadURLRequest* UPostDataUploadURLRequest::Make(TArray<UUploadRequestBody*> _Request, FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostDataUploadURLRequest* Req = NewObject<UPostDataUploadURLRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUploadRequests>(Req);
	Req->Body->Request = _Request;
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
