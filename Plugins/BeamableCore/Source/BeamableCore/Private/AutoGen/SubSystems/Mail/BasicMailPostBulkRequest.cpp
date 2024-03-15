
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/BasicMailPostBulkRequest.h"

void UBasicMailPostBulkRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBasicMailPostBulkRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/mail/bulk");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicMailPostBulkRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicMailPostBulkRequest* UBasicMailPostBulkRequest::Make(TArray<USendMailRequestBody*> _SendMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicMailPostBulkRequest* Req = NewObject<UBasicMailPostBulkRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBulkSendMailRequestBody>(Req);
	Req->Body->SendMailRequests = _SendMailRequests;
	

	return Req;
}
