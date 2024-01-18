
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostCatalogLegacyRequest.h"

void UPostCatalogLegacyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostCatalogLegacyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/commerce/catalog/legacy");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostCatalogLegacyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCatalogLegacyRequest* UPostCatalogLegacyRequest::Make(TArray<UStore*> _Stores, TArray<UOfferDefinition*> _OfferDefinitions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostCatalogLegacyRequest* Req = NewObject<UPostCatalogLegacyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USaveCatalogRequestBody>(Req);
	Req->Body->Stores = _Stores;
	Req->Body->OfferDefinitions = _OfferDefinitions;
	

	return Req;
}
