
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PutBulkRequest.h"

void UPutBulkRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutBulkRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/bulk");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutBulkRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutBulkRequest* UPutBulkRequest::Make(int64 _ObjectId, TArray<UMyMailUpdate*> _UpdateMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutBulkRequest* Req = NewObject<UPutBulkRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBulkUpdateMailObjectRequestBody>(Req);
	Req->Body->UpdateMailRequests = _UpdateMailRequests;
	

	return Req;
}
