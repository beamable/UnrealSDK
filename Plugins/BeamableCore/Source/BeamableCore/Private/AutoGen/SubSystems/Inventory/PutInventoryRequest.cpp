
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PutInventoryRequest.h"

void UPutInventoryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutInventoryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutInventoryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutInventoryRequest* UPutInventoryRequest::Make(FBeamGamerTag _ObjectId, FOptionalBool _bApplyVipBonus, FOptionalString _Transaction, FOptionalArrayOfItemUpdateRequestBody _UpdateItems, FOptionalArrayOfItemCreateRequestBody _NewItems, FOptionalArrayOfItemDeleteRequestBody _DeleteItems, FOptionalMapOfInt64 _Currencies, FOptionalMapOfArrayOfCurrencyProperty _CurrencyProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutInventoryRequest* Req = NewObject<UPutInventoryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UInventoryUpdateRequestBody>(Req);
	Req->Body->bApplyVipBonus = _bApplyVipBonus;
	Req->Body->Transaction = _Transaction;
	Req->Body->UpdateItems = _UpdateItems;
	Req->Body->NewItems = _NewItems;
	Req->Body->DeleteItems = _DeleteItems;
	Req->Body->Currencies = _Currencies;
	Req->Body->CurrencyProperties = _CurrencyProperties;
	

	return Req;
}
