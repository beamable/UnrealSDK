
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/MSPlayground/MSPlaygroundTestArrRequest.h"

void UMSPlaygroundTestArrRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UMSPlaygroundTestArrRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_MSPlayground/TestArr");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UMSPlaygroundTestArrRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UMSPlaygroundTestArrRequest* UMSPlaygroundTestArrRequest::Make(int32 _A, int32 _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UMSPlaygroundTestArrRequest* Req = NewObject<UMSPlaygroundTestArrRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTestArrRequestArgs>(Req);
	Req->Body->A = _A;
	Req->Body->B = _B;
	

	return Req;
}
