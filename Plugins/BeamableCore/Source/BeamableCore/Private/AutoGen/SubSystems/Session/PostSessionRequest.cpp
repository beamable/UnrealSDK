
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostSessionRequest.h"

void UPostSessionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSessionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/session/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSessionRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSessionRequest* UPostSessionRequest::Make(FOptionalString _Source, FOptionalString _Shard, FOptionalString _Locale, FOptionalSessionLanguageContext _Language, FOptionalInt64 _Time, FOptionalString _Platform, FOptionalInt64 _Gamer, FOptionalString _Device, FOptionalMapOfString _CustomParams, FOptionalMapOfString _DeviceParams, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSessionRequest* Req = NewObject<UPostSessionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStartSessionRequestBody>(Req);
	Req->Body->Source = _Source;
	Req->Body->Shard = _Shard;
	Req->Body->Locale = _Locale;
	Req->Body->Language = _Language;
	Req->Body->Time = _Time;
	Req->Body->Platform = _Platform;
	Req->Body->Gamer = _Gamer;
	Req->Body->Device = _Device;
	Req->Body->CustomParams = _CustomParams;
	Req->Body->DeviceParams = _DeviceParams;
	

	return Req;
}
