
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostCustomerRequest.h"

void UPostCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostCustomerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCustomerRequest* UPostCustomerRequest::Make(FString _ProjectName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostCustomerRequest* Req = NewObject<UPostCustomerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UNewCustomerRequestBody>(Req);
	Req->Body->ProjectName = _ProjectName;
	Req->Body->Email = _Email;
	Req->Body->Password = _Password;
	Req->Body->bHierarchy = _bHierarchy;
	Req->Body->CustomerName = _CustomerName;
	Req->Body->Alias = _Alias;
	

	return Req;
}
