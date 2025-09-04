
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostCustomersRequest.h"

void UPostCustomersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostCustomersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostCustomersRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCustomersRequest* UPostCustomersRequest::Make(FString _RealmName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostCustomersRequest* Req = NewObject<UPostCustomersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCustomerActorNewCustomerRequestBody>(Req);
	Req->Body->RealmName = _RealmName;
	Req->Body->Email = _Email;
	Req->Body->Password = _Password;
	Req->Body->bHierarchy = _bHierarchy;
	Req->Body->CustomerName = _CustomerName;
	Req->Body->Alias = _Alias;
	

	return Req;
}
