
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostPurchaseRequest.h"

void UPostPurchaseRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPurchaseRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/purchase");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPurchaseRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPurchaseRequest* UPostPurchaseRequest::Make(int64 _ObjectId, FString _PurchaseId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPurchaseRequest* Req = NewObject<UPostPurchaseRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPurchaseRequestBody>(Req);
	Req->Body->PurchaseId = _PurchaseId;
	

	return Req;
}
