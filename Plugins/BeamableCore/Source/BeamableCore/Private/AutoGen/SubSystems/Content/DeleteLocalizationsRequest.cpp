
#include "BeamableCore/Public/AutoGen/SubSystems/Content/DeleteLocalizationsRequest.h"

void UDeleteLocalizationsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteLocalizationsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/localizations");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteLocalizationsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteLocalizationsRequest* UDeleteLocalizationsRequest::Make(TArray<ULocalizationQuery*> _Localizations, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteLocalizationsRequest* Req = NewObject<UDeleteLocalizationsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteLocalizationRequestBody>(Req);
	Req->Body->Localizations = _Localizations;
	

	return Req;
}
