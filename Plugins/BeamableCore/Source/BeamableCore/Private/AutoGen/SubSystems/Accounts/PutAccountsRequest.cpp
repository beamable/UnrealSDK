
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutAccountsRequest.h"

void UPutAccountsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAccountsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAccountsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAccountsRequest* UPutAccountsRequest::Make(FBeamAccountId _ObjectId, bool _bHasThirdPartyToken, FOptionalString _ThirdParty, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, FOptionalArrayOfBeamExternalIdentity _External, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutAccountsRequest* Req = NewObject<UPutAccountsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

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
	Req->Body->External = _External;
	

	return Req;
}
