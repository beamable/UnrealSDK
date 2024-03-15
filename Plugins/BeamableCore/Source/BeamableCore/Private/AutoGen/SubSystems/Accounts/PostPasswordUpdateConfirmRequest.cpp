
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostPasswordUpdateConfirmRequest.h"

void UPostPasswordUpdateConfirmRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPasswordUpdateConfirmRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/password-update/confirm");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPasswordUpdateConfirmRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPasswordUpdateConfirmRequest* UPostPasswordUpdateConfirmRequest::Make(FString _Code, FString _NewPassword, FOptionalString _Email, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPasswordUpdateConfirmRequest* Req = NewObject<UPostPasswordUpdateConfirmRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPasswordUpdateConfirmation>(Req);
	Req->Body->Code = _Code;
	Req->Body->NewPassword = _NewPassword;
	Req->Body->Email = _Email;
	

	return Req;
}
