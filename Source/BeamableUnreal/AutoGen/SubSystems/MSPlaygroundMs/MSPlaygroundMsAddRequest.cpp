
#include "BeamableUnreal\AutoGen/SubSystems/MSPlaygroundMs/MSPlaygroundMsAddRequest.h"

void UMSPlaygroundMsAddRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UMSPlaygroundMsAddRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_MSPlayground/Add");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UMSPlaygroundMsAddRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UMSPlaygroundMsAddRequest* UMSPlaygroundMsAddRequest::Make(int32 _A, int32 _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UMSPlaygroundMsAddRequest* Req = NewObject<UMSPlaygroundMsAddRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMSPlaygroundAddRequestArgs>(Req);
	Req->Body->A = _A;
	Req->Body->B = _B;
	

	return Req;
}
