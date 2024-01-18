
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PutTransferRequest.h"

void UPutTransferRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutTransferRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/transfer");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutTransferRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutTransferRequest* UPutTransferRequest::Make(FBeamGamerTag _ObjectId, FBeamGamerTag _RecipientPlayer, FOptionalString _Transaction, FOptionalMapOfInt64 _Currencies, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutTransferRequest* Req = NewObject<UPutTransferRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UTransferRequestBody>(Req);
	Req->Body->RecipientPlayer = _RecipientPlayer;
	Req->Body->Transaction = _Transaction;
	Req->Body->Currencies = _Currencies;
	

	return Req;
}
