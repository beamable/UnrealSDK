
#include "PostStatsUpdateRequest.h"

void UPostStatsUpdateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostStatsUpdateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/stats/update");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostStatsUpdateRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostStatsUpdateRequest* UPostStatsUpdateRequest::MakePostStatsUpdateRequest(int64 _ObjectId, TMap<FString, FString> _StatsBefore, TMap<FString, FString> _StatsAfter, UObject* Outer)
{
	UPostStatsUpdateRequest* Req = NewObject<UPostStatsUpdateRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStatSubscriptionNotification>(Req);
	Req->Body->StatsBefore = _StatsBefore;
	Req->Body->StatsAfter = _StatsAfter;
	

	return Req;
}