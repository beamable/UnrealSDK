
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutMeRequest.h"

void UPutMeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutMeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/me");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutMeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutMeRequest* UPutMeRequest::Make(bool _bHasThirdPartyToken, FOptionalString _ThirdParty, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, FOptionalArrayOfBeamExternalIdentity _External, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutMeRequest* Req = NewObject<UPutMeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
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
