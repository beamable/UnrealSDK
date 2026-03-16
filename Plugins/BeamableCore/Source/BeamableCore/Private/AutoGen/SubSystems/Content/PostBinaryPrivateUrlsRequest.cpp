
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostBinaryPrivateUrlsRequest.h"

void UPostBinaryPrivateUrlsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostBinaryPrivateUrlsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/binary/private/urls");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostBinaryPrivateUrlsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostBinaryPrivateUrlsRequest* UPostBinaryPrivateUrlsRequest::Make(TArray<UGetContentRequestBody*> _Requests, FOptionalInt64 _ExpirationSeconds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostBinaryPrivateUrlsRequest* Req = NewObject<UPostBinaryPrivateUrlsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetBinaryDownloadUrlsRequestBody>(Req);
	Req->Body->Requests = _Requests;
	Req->Body->ExpirationSeconds = _ExpirationSeconds;
	

	return Req;
}
