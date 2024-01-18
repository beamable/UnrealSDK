
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostBinaryRequest.h"

void UPostBinaryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostBinaryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/binary");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostBinaryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostBinaryRequest* UPostBinaryRequest::Make(TArray<UBinaryDefinition*> _Binary, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostBinaryRequest* Req = NewObject<UPostBinaryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USaveBinaryRequestBody>(Req);
	Req->Body->Binary = _Binary;
	

	return Req;
}
