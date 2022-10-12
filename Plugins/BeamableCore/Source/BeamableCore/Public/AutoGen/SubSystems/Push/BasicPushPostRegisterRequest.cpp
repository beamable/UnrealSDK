
#include "BasicPushPostRegisterRequest.h"

void UBasicPushPostRegisterRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBasicPushPostRegisterRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/push/register");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicPushPostRegisterRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicPushPostRegisterRequest* UBasicPushPostRegisterRequest::MakeBasicPushPostRegisterRequest(FString _Provider, FString _Token, UObject* Outer)
{
	UBasicPushPostRegisterRequest* Req = NewObject<UBasicPushPostRegisterRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URegisterReq>(Req);
	Req->Body->Provider = _Provider;
	Req->Body->Token = _Token;
	

	return Req;
}
