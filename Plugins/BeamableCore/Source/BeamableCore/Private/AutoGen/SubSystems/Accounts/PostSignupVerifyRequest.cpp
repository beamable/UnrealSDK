
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostSignupVerifyRequest.h"

void UPostSignupVerifyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSignupVerifyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/signup/verify");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSignupVerifyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSignupVerifyRequest* UPostSignupVerifyRequest::Make(FString _Email, FString _Code, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSignupVerifyRequest* Req = NewObject<UPostSignupVerifyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USignupVerificationRequestBody>(Req);
	Req->Body->Email = _Email;
	Req->Body->Code = _Code;
	

	return Req;
}
