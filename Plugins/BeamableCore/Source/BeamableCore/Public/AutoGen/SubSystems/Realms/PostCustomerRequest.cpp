
#include "PostCustomerRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCustomerRequest* UPostCustomerRequest::MakePostCustomerRequest(FString _ProjectName, FString _Email, FOptionalString _CustomerName, FOptionalBool _bHierarchy, FOptionalString _Alias, FString _Password, UObject* Outer)
{
	UPostCustomerRequest* Req = NewObject<UPostCustomerRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UNewCustomerRequestBody>(Req);
	Req->Body->ProjectName = _ProjectName;
	Req->Body->Email = _Email;
	Req->Body->CustomerName = _CustomerName;
	Req->Body->bHierarchy = _bHierarchy;
	Req->Body->Alias = _Alias;
	Req->Body->Password = _Password;
	

	return Req;
}
