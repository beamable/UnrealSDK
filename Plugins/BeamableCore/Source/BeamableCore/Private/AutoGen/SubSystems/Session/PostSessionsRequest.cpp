
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostSessionsRequest.h"

void UPostSessionsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSessionsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/sessions");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSessionsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSessionsRequest* UPostSessionsRequest::Make(FOptionalString _Platform, FOptionalString _Device, FOptionalString _Source, FOptionalString _Locale, FOptionalSessionLanguageContextDto _Language, FOptionalMapOfString _CustomParams, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSessionsRequest* Req = NewObject<UPostSessionsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USessionActorStartSessionRequestBody>(Req);
	Req->Body->Platform = _Platform;
	Req->Body->Device = _Device;
	Req->Body->Source = _Source;
	Req->Body->Locale = _Locale;
	Req->Body->Language = _Language;
	Req->Body->CustomParams = _CustomParams;
	

	return Req;
}
