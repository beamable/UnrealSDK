
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetCustomerActivateRequest.h"

void UGetCustomerActivateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetCustomerActivateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customer/activate");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("token"), *Token);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("cid"), *FString::FromInt(Cid));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetCustomerActivateRequest::BuildBody(FString& BodyString) const
{
	
}

UGetCustomerActivateRequest* UGetCustomerActivateRequest::Make(FString _Token, int64 _Cid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetCustomerActivateRequest* Req = NewObject<UGetCustomerActivateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Token = _Token;
	Req->Cid = _Cid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
