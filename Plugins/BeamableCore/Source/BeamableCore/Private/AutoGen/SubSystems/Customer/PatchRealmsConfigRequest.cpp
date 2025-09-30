
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PatchRealmsConfigRequest.h"

void UPatchRealmsConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PATCH");
}

void UPatchRealmsConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/realms/{realmId}/config");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	Route = Route.Replace(TEXT("{realmId}"), *RealmId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPatchRealmsConfigRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPatchRealmsConfigRequest* UPatchRealmsConfigRequest::Make(FString _CustomerId, FString _RealmId, FOptionalArrayOfString _Deletes, FOptionalMapOfString _Upserts, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPatchRealmsConfigRequest* Req = NewObject<UPatchRealmsConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	Req->RealmId = _RealmId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URealmConfigChangeRequestBody>(Req);
	Req->Body->Deletes = _Deletes;
	Req->Body->Upserts = _Upserts;
	

	return Req;
}
