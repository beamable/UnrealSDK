
#include "AutoGen/SubSystems/Accounts/PutAdminThirdPartyRequest.h"

void UPutAdminThirdPartyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAdminThirdPartyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/admin/third-party");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAdminThirdPartyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAdminThirdPartyRequest* UPutAdminThirdPartyRequest::Make(int64 _ObjectId, int64 _FromAccountId, UThirdPartyAssociation* _ThirdParty, UObject* Outer)
{
	UPutAdminThirdPartyRequest* Req = NewObject<UPutAdminThirdPartyRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTransferThirdPartyAssociation>(Req);
	Req->Body->FromAccountId = _FromAccountId;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->ThirdParty->Rename(nullptr, Req);
	

	return Req;
}
