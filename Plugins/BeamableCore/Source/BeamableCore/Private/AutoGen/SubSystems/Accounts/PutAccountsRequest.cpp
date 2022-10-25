
#include "AutoGen/SubSystems/Accounts/PutAccountsRequest.h"

void UPutAccountsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAccountsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAccountsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAccountsRequest* UPutAccountsRequest::Make(int64 _ObjectId, bool _bHasThirdPartyToken, FOptionalString _ThirdParty, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, UObject* Outer)
{
	UPutAccountsRequest* Req = NewObject<UPutAccountsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAccountUpdate>(Req);
	Req->Body->bHasThirdPartyToken = _bHasThirdPartyToken;
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->Country = _Country;
	Req->Body->Language = _Language;
	Req->Body->GamerTagAssoc = _GamerTagAssoc;
	Req->Body->Token = _Token;
	Req->Body->DeviceId = _DeviceId;
	Req->Body->UserName = _UserName;
	

	return Req;
}
