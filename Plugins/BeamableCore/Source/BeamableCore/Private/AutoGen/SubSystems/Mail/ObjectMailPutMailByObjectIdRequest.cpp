
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPutMailByObjectIdRequest.h"

void UObjectMailPutMailByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UObjectMailPutMailByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectMailPutMailByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectMailPutMailByObjectIdRequest* UObjectMailPutMailByObjectIdRequest::Make(int64 _ObjectId, int64 _MailId, FOptionalBool _bAcceptAttachments, FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, FOptionalString _Category, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectMailPutMailByObjectIdRequest* Req = NewObject<UObjectMailPutMailByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateMailRequestBody>(Req);
	Req->Body->MailId = _MailId;
	Req->Body->bAcceptAttachments = _bAcceptAttachments;
	Req->Body->Body = _Body;
	Req->Body->Expires = _Expires;
	Req->Body->Subject = _Subject;
	Req->Body->State = _State;
	Req->Body->Category = _Category;
	

	return Req;
}
