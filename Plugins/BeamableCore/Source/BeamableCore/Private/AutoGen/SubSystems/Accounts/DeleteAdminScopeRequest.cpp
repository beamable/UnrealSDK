
#include "AutoGen/SubSystems/Accounts/DeleteAdminScopeRequest.h"

void UDeleteAdminScopeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteAdminScopeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/admin/scope");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteAdminScopeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteAdminScopeRequest* UDeleteAdminScopeRequest::Make(int64 _ObjectId, FString _Realm, FString _Role, UObject* RequestOwner)
{
	UDeleteAdminScopeRequest* Req = NewObject<UDeleteAdminScopeRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteRoleRequestBody>(Req);
	Req->Body->Realm = _Realm;
	Req->Body->Role = _Role;
	

	return Req;
}
