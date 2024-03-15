
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteRoleRequest.h"

void UDeleteRoleRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteRoleRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/role");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteRoleRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteRoleRequest* UDeleteRoleRequest::Make(FBeamAccountId _ObjectId, FOptionalBeamPid _Realm, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteRoleRequest* Req = NewObject<UDeleteRoleRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteRoleRequestBody>(Req);
	Req->Body->Realm = _Realm;
	Req->Body->Role = _Role;
	

	return Req;
}
