
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PutLocalizationsRequest.h"

void UPutLocalizationsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutLocalizationsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/localizations");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutLocalizationsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutLocalizationsRequest* UPutLocalizationsRequest::Make(TMap<FString, FArrayOfLocalizedValue> _Localizations, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutLocalizationsRequest* Req = NewObject<UPutLocalizationsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPutLocalizationsRequestBody>(Req);
	Req->Body->Localizations = _Localizations;
	

	return Req;
}
