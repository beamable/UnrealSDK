
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PutAcceptManyRequest.h"

void UPutAcceptManyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAcceptManyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/accept/many");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAcceptManyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAcceptManyRequest* UPutAcceptManyRequest::Make(int64 _ObjectId, TArray<int64> _MailIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutAcceptManyRequest* Req = NewObject<UPutAcceptManyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAcceptMultipleAttachments>(Req);
	Req->Body->MailIds = _MailIds;
	

	return Req;
}
