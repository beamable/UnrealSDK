
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteAdminThirdPartyRequest.h"

void UDeleteAdminThirdPartyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteAdminThirdPartyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/admin/third-party");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteAdminThirdPartyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteAdminThirdPartyRequest* UDeleteAdminThirdPartyRequest::Make(FBeamAccountId _ObjectId, FString _ThirdParty, FString _UserAppId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteAdminThirdPartyRequest* Req = NewObject<UDeleteAdminThirdPartyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteThirdPartyAssociation>(Req);
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->UserAppId = _UserAppId;
	

	return Req;
}
