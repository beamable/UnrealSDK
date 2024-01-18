
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PutAttachmentsRequest.h"

void UPutAttachmentsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAttachmentsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/mail/attachments");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAttachmentsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAttachmentsRequest* UPutAttachmentsRequest::Make(TArray<int64> _MailIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutAttachmentsRequest* Req = NewObject<UPutAttachmentsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAcceptMultipleAttachments>(Req);
	Req->Body->MailIds = _MailIds;
	

	return Req;
}
