
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PutPurchaseRequest.h"

void UPutPurchaseRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPurchaseRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/purchase");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPurchaseRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutPurchaseRequest* UPutPurchaseRequest::Make(int64 _ObjectId, FString _ListingId, FOptionalBool _bFree, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPurchaseRequest* Req = NewObject<UPutPurchaseRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UReportPurchaseRequestBody>(Req);
	Req->Body->ListingId = _ListingId;
	Req->Body->bFree = _bFree;
	

	return Req;
}
