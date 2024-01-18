
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/BasicMailPutMailRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicMailPutMailRequest* UBasicMailPutMailRequest::Make(int64 _MailId, FOptionalBool _bAcceptAttachments, FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, FOptionalString _Category, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicMailPutMailRequest* Req = NewObject<UBasicMailPutMailRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
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
