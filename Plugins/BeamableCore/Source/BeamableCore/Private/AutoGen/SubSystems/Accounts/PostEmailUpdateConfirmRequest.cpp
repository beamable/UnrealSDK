
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostEmailUpdateConfirmRequest.h"

void UPostEmailUpdateConfirmRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostEmailUpdateConfirmRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/email-update/confirm");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostEmailUpdateConfirmRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostEmailUpdateConfirmRequest* UPostEmailUpdateConfirmRequest::Make(FString _Code, FString _Password, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostEmailUpdateConfirmRequest* Req = NewObject<UPostEmailUpdateConfirmRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEmailUpdateConfirmation>(Req);
	Req->Body->Code = _Code;
	Req->Body->Password = _Password;
	

	return Req;
}
