
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutRealmsConfigRequest.h"

void UPutRealmsConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutRealmsConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/realms/{realmId}/config");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	Route = Route.Replace(TEXT("{realmId}"), *RealmId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutRealmsConfigRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutRealmsConfigRequest* UPutRealmsConfigRequest::Make(FString _CustomerId, FString _RealmId, FOptionalMapOfString _Config, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutRealmsConfigRequest* Req = NewObject<UPutRealmsConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	Req->RealmId = _RealmId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URealmConfigSaveRequestBody>(Req);
	Req->Body->Config = _Config;
	

	return Req;
}
