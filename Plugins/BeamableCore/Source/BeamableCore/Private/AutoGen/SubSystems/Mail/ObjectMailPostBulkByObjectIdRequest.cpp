
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPostBulkByObjectIdRequest.h"

void UObjectMailPostBulkByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectMailPostBulkByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/bulk");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectMailPostBulkByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectMailPostBulkByObjectIdRequest* UObjectMailPostBulkByObjectIdRequest::Make(int64 _ObjectId, TArray<USendMailRequestBody*> _SendMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectMailPostBulkByObjectIdRequest* Req = NewObject<UObjectMailPostBulkByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBulkSendMailRequestBody>(Req);
	Req->Body->SendMailRequests = _SendMailRequests;
	

	return Req;
}
