
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/ObjectAccountsPutRoleByObjectIdRequest.h"

void UObjectAccountsPutRoleByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UObjectAccountsPutRoleByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/role");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectAccountsPutRoleByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectAccountsPutRoleByObjectIdRequest* UObjectAccountsPutRoleByObjectIdRequest::Make(FBeamAccountId _ObjectId, FOptionalBeamCid _Cid, FOptionalBeamPid _Realm, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectAccountsPutRoleByObjectIdRequest* Req = NewObject<UObjectAccountsPutRoleByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateRole>(Req);
	Req->Body->Cid = _Cid;
	Req->Body->Realm = _Realm;
	Req->Body->Role = _Role;
	

	return Req;
}
