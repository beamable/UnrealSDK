
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/ObjectAccountsPutRoleRequest.h"

void UObjectAccountsPutRoleRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UObjectAccountsPutRoleRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/role");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectAccountsPutRoleRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectAccountsPutRoleRequest* UObjectAccountsPutRoleRequest::Make(FBeamAccountId _ObjectId, FOptionalBeamCid _Cid, FOptionalBeamPid _Realm, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectAccountsPutRoleRequest* Req = NewObject<UObjectAccountsPutRoleRequest>(RequestOwner);
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
