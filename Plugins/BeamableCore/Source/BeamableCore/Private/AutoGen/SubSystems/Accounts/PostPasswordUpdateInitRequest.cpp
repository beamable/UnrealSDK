
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostPasswordUpdateInitRequest.h"

void UPostPasswordUpdateInitRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPasswordUpdateInitRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/password-update/init");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPasswordUpdateInitRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPasswordUpdateInitRequest* UPostPasswordUpdateInitRequest::Make(FString _Email, FOptionalString _CodeType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPasswordUpdateInitRequest* Req = NewObject<UPostPasswordUpdateInitRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPasswordUpdateRequestBody>(Req);
	Req->Body->Email = _Email;
	Req->Body->CodeType = _CodeType;
	

	return Req;
}
