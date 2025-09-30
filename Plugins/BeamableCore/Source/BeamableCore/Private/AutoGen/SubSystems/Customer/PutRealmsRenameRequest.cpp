
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutRealmsRenameRequest.h"

void UPutRealmsRenameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutRealmsRenameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/realms/{realmId}/rename");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	Route = Route.Replace(TEXT("{realmId}"), *RealmId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutRealmsRenameRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutRealmsRenameRequest* UPutRealmsRenameRequest::Make(FString _CustomerId, FString _RealmId, FString _NewName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutRealmsRenameRequest* Req = NewObject<UPutRealmsRenameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	Req->RealmId = _RealmId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URenameRealmRequestBody>(Req);
	Req->Body->NewName = _NewName;
	

	return Req;
}
