
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PutSwapRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutSwapRequest* UPutSwapRequest::Make(FString _ObjectId, int64 _SwapBase, int64 _Delta, FOptionalInt64 _WinnerId, FOptionalInt64 _LoserId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutSwapRequest* Req = NewObject<UPutSwapRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardSwapRequestBody>(Req);
	Req->Body->SwapBase = _SwapBase;
	Req->Body->Delta = _Delta;
	Req->Body->WinnerId = _WinnerId;
	Req->Body->LoserId = _LoserId;
	

	return Req;
}
