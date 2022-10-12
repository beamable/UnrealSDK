
#include "BasicMailPutMailRequest.h"

void UBasicMailPutMailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UBasicMailPutMailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/mail/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicMailPutMailRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicMailPutMailRequest* UBasicMailPutMailRequest::MakeBasicMailPutMailRequest(FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, int64 _MailId, FOptionalString _Category, FOptionalBool _bAcceptAttachments, UObject* Outer)
{
	UBasicMailPutMailRequest* Req = NewObject<UBasicMailPutMailRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateMailRequestBody>(Req);
	Req->Body->Body = _Body;
	Req->Body->Expires = _Expires;
	Req->Body->Subject = _Subject;
	Req->Body->State = _State;
	Req->Body->MailId = _MailId;
	Req->Body->Category = _Category;
	Req->Body->bAcceptAttachments = _bAcceptAttachments;
	

	return Req;
}
