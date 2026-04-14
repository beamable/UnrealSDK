
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/DeleteTokensRequest.h"

void UDeleteTokensRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteTokensRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteTokensRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteTokensRequest* UDeleteTokensRequest::Make(TArray<FString> _Tokens, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteTokensRequest* Req = NewObject<UDeleteTokensRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAuthV2RevokeRefreshTokensRequestBody>(Req);
	Req->Body->Tokens = _Tokens;
	

	return Req;
}
