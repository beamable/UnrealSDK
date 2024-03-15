
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteMeThirdPartyRequest.h"

void UDeleteMeThirdPartyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteMeThirdPartyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/me/third-party");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteMeThirdPartyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteMeThirdPartyRequest* UDeleteMeThirdPartyRequest::Make(FString _ThirdParty, FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteMeThirdPartyRequest* Req = NewObject<UDeleteMeThirdPartyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UThirdPartyAvailableRequestBody>(Req);
	Req->Body->ThirdParty = _ThirdParty;
	Req->Body->Token = _Token;
	

	return Req;
}
