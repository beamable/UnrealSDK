
#include "PutSwapRequest.h"

void UPutSwapRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutSwapRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/swap");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutSwapRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutSwapRequest* UPutSwapRequest::MakePutSwapRequest(FString _ObjectId, FOptionalInt64 _WinnerId, FOptionalInt64 _LoserId, int64 _SwapBase, int64 _Delta, UObject* Outer)
{
	UPutSwapRequest* Req = NewObject<UPutSwapRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardSwapRequestBody>(Req);
	Req->Body->WinnerId = _WinnerId;
	Req->Body->LoserId = _LoserId;
	Req->Body->SwapBase = _SwapBase;
	Req->Body->Delta = _Delta;
	

	return Req;
}
