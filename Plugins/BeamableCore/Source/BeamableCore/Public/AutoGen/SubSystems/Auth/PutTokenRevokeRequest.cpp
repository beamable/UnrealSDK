
#include "PutTokenRevokeRequest.h"

void UPutTokenRevokeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutTokenRevokeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/auth/token/revoke");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutTokenRevokeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutTokenRevokeRequest* UPutTokenRevokeRequest::MakePutTokenRevokeRequest(FString _Token, UObject* Outer)
{
	UPutTokenRevokeRequest* Req = NewObject<UPutTokenRevokeRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URevokeTokenRequestBody>(Req);
	Req->Body->Token = _Token;
	

	return Req;
}