
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamAuthRequest.h"

void UPostSteamAuthRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSteamAuthRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/steam/auth");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSteamAuthRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSteamAuthRequest* UPostSteamAuthRequest::Make(FString _Ticket, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSteamAuthRequest* Req = NewObject<UPostSteamAuthRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USteamAuthRequestBody>(Req);
	Req->Body->Ticket = _Ticket;
	

	return Req;
}
