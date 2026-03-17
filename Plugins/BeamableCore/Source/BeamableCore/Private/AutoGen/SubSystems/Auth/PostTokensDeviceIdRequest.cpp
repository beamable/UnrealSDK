
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensDeviceIdRequest.h"

void UPostTokensDeviceIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTokensDeviceIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/device-id");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTokensDeviceIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTokensDeviceIdRequest* UPostTokensDeviceIdRequest::Make(FOptionalString _DeviceId, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTokensDeviceIdRequest* Req = NewObject<UPostTokensDeviceIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAuthV2DeviceIdAuthRequestBody>(Req);
	Req->Body->DeviceId = _DeviceId;
	Req->Body->Scope = _Scope;
	Req->Body->CustomerId = _CustomerId;
	Req->Body->RealmId = _RealmId;
	Req->Body->Context = _Context;
	

	return Req;
}
