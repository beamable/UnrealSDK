
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostImageUrlsRequest.h"

void UPostImageUrlsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostImageUrlsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/image/urls");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostImageUrlsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostImageUrlsRequest* UPostImageUrlsRequest::Make(TArray<UServiceImageLayers*> _Requests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostImageUrlsRequest* Req = NewObject<UPostImageUrlsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetServiceURLsRequestBody>(Req);
	Req->Body->Requests = _Requests;
	

	return Req;
}
