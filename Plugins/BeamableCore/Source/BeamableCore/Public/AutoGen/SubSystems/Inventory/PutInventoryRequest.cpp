
#include "PutInventoryRequest.h"

void UPutInventoryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutInventoryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutInventoryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutInventoryRequest* UPutInventoryRequest::MakePutInventoryRequest(int64 _ObjectId, FOptionalMapOfInt64 _Currencies, bool _bEmpty, FOptionalMapOfArrayOfCurrencyProperty _CurrencyProperties, TArray<FString> _CurrencyContentIds, FOptionalBool _bApplyVipBonus, TArray<FString> _ItemContentIds, FOptionalArrayOfItemUpdateRequestBody _UpdateItems, FOptionalArrayOfItemCreateRequestBody _NewItems, FOptionalString _Transaction, FOptionalArrayOfItemDeleteRequestBody _DeleteItems, UObject* Outer)
{
	UPutInventoryRequest* Req = NewObject<UPutInventoryRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UInventoryUpdateRequestBody>(Req);
	Req->Body->Currencies = _Currencies;
	Req->Body->bEmpty = _bEmpty;
	Req->Body->CurrencyProperties = _CurrencyProperties;
	Req->Body->CurrencyContentIds = _CurrencyContentIds;
	Req->Body->bApplyVipBonus = _bApplyVipBonus;
	Req->Body->ItemContentIds = _ItemContentIds;
	Req->Body->UpdateItems = _UpdateItems;
	Req->Body->NewItems = _NewItems;
	Req->Body->Transaction = _Transaction;
	Req->Body->DeleteItems = _DeleteItems;
	

	return Req;
}
