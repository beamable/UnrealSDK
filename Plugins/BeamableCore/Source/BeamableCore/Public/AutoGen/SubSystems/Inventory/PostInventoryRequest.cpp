
#include "PostInventoryRequest.h"

void UPostInventoryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostInventoryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostInventoryRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostInventoryRequest* UPostInventoryRequest::MakePostInventoryRequest(int64 _ObjectId, FOptionalArrayOfString _Scopes, UObject* Outer)
{
	UPostInventoryRequest* Req = NewObject<UPostInventoryRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UInventoryQueryRequestBody>(Req);
	Req->Body->Scopes = _Scopes;
	

	return Req;
}
