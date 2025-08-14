
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/MSPlayground/MSPlaygroundTestNotificationRequest.h"

void UMSPlaygroundTestNotificationRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UMSPlaygroundTestNotificationRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_MSPlayground/TestNotification");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UMSPlaygroundTestNotificationRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UMSPlaygroundTestNotificationRequest* UMSPlaygroundTestNotificationRequest::Make(FString _A, FString _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UMSPlaygroundTestNotificationRequest* Req = NewObject<UMSPlaygroundTestNotificationRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTestNotificationRequestArgs>(Req);
	Req->Body->A = _A;
	Req->Body->B = _B;
	

	return Req;
}
