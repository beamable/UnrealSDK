
#include "PutAdminEmailRequest.h"

void UPutAdminEmailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAdminEmailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/admin/email");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAdminEmailRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAdminEmailRequest* UPutAdminEmailRequest::MakePutAdminEmailRequest(int64 _ObjectId, FString _NewEmail, FOptionalString _CodeType, UObject* Outer)
{
	UPutAdminEmailRequest* Req = NewObject<UPutAdminEmailRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEmailUpdateRequestBody>(Req);
	Req->Body->NewEmail = _NewEmail;
	Req->Body->CodeType = _CodeType;
	

	return Req;
}
