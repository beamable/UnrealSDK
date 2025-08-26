
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutAliasRequest.h"

void UPutAliasRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAliasRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/alias");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAliasRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAliasRequest* UPutAliasRequest::Make(FString _CustomerId, FString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutAliasRequest* Req = NewObject<UPutAliasRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USetCustomerAliasRequestBody>(Req);
	Req->Body->Alias = _Alias;
	

	return Req;
}
