
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLRequest.h"

void UPostDataDownloadURLRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostDataDownloadURLRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/downloadURL");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostDataDownloadURLRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostDataDownloadURLRequest* UPostDataDownloadURLRequest::Make(FOptionalInt64 _PlayerId, FOptionalArrayOfObjectRequestBody _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostDataDownloadURLRequest* Req = NewObject<UPostDataDownloadURLRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UObjectRequests>(Req);
	Req->Body->PlayerId = _PlayerId;
	Req->Body->Request = _Request;
	

	return Req;
}
