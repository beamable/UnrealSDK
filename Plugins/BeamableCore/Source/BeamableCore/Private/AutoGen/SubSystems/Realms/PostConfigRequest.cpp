
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostConfigRequest.h"

void UPostConfigRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostConfigRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/config");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostConfigRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostConfigRequest* UPostConfigRequest::Make(FOptionalArrayOfString _Deletes, FOptionalMapOfString _Upserts, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostConfigRequest* Req = NewObject<UPostConfigRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URealmConfigChangeRequestBody>(Req);
	Req->Body->Deletes = _Deletes;
	Req->Body->Upserts = _Upserts;
	

	return Req;
}
