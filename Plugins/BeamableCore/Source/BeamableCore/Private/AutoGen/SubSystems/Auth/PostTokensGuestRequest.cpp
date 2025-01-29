
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensGuestRequest.h"

void UPostTokensGuestRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTokensGuestRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/guest");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTokensGuestRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTokensGuestRequest* UPostTokensGuestRequest::Make(FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalContextInfo _Context, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTokensGuestRequest* Req = NewObject<UPostTokensGuestRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGuestAuthRequestBody>(Req);
	Req->Body->Scope = _Scope;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	Req->Body->InitProperties = _InitProperties;
	

	return Req;
}
