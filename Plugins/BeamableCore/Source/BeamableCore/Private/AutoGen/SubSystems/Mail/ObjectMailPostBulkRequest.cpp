
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPostBulkRequest.h"

void UObjectMailPostBulkRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectMailPostBulkRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/bulk");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectMailPostBulkRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectMailPostBulkRequest* UObjectMailPostBulkRequest::Make(int64 _ObjectId, TArray<USendMailRequestBody*> _SendMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectMailPostBulkRequest* Req = NewObject<UObjectMailPostBulkRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBulkSendMailRequestBody>(Req);
	Req->Body->SendMailRequests = _SendMailRequests;
	

	return Req;
}
