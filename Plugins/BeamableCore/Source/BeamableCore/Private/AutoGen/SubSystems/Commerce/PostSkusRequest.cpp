
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostSkusRequest.h"

void UPostSkusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSkusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/commerce/skus");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSkusRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSkusRequest* UPostSkusRequest::Make(TArray<USKU*> _Definitions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSkusRequest* Req = NewObject<UPostSkusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USaveSKUsRequestBody>(Req);
	Req->Body->Definitions = _Definitions;
	

	return Req;
}
