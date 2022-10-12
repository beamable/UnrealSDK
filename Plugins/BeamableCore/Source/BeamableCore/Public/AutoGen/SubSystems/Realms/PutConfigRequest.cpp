
#include "PutConfigRequest.h"

void UPutConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/config");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutConfigRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutConfigRequest* UPutConfigRequest::MakePutConfigRequest(TMap<FString, FString> _Config, UObject* Outer)
{
	UPutConfigRequest* Req = NewObject<UPutConfigRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URealmConfigSaveRequestBody>(Req);
	Req->Body->Config = _Config;
	

	return Req;
}
