
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostSignupRequest.h"

void UPostSignupRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSignupRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/signup");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSignupRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSignupRequest* UPostSignupRequest::Make(FOptionalString _Username, FOptionalString _ProviderNamespace, FOptionalChallengeSolution _ChallengeSolution, FOptionalString _ExternalToken, FOptionalString _ProviderService, FOptionalString _Password, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSignupRequest* Req = NewObject<UPostSignupRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateAccountWithCredsRequestBody>(Req);
	Req->Body->Username = _Username;
	Req->Body->ProviderNamespace = _ProviderNamespace;
	Req->Body->ChallengeSolution = _ChallengeSolution;
	Req->Body->ExternalToken = _ExternalToken;
	Req->Body->ProviderService = _ProviderService;
	Req->Body->Password = _Password;
	Req->Body->InitProperties = _InitProperties;
	

	return Req;
}
