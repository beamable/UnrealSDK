
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/DeleteTransactionRequest.h"

void UDeleteTransactionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteTransactionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/transaction");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteTransactionRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteTransactionRequest* UDeleteTransactionRequest::Make(FBeamGamerTag _ObjectId, FString _Transaction, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteTransactionRequest* Req = NewObject<UDeleteTransactionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEndTransactionRequestBody>(Req);
	Req->Body->Transaction = _Transaction;
	

	return Req;
}
