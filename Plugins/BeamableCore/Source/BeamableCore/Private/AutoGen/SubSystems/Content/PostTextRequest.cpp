
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostTextRequest.h"

void UPostTextRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostTextRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/text");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostTextRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostTextRequest* UPostTextRequest::Make(TArray<UTextDefinition*> _Text, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostTextRequest* Req = NewObject<UPostTextRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USaveTextRequestBody>(Req);
	Req->Body->Text = _Text;
	

	return Req;
}
