
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/MSPlayground/MSPlaygroundAddRequest.h"

void UMSPlaygroundAddRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UMSPlaygroundAddRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_MSPlayground/Add");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UMSPlaygroundAddRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UMSPlaygroundAddRequest* UMSPlaygroundAddRequest::Make(int32 _A, int32 _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UMSPlaygroundAddRequest* Req = NewObject<UMSPlaygroundAddRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAddRequestArgs>(Req);
	Req->Body->A = _A;
	Req->Body->B = _B;
	

	return Req;
}
