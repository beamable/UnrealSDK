
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/DeleteClientSubscriptionsRequest.h"

void UDeleteClientSubscriptionsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteClientSubscriptionsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/stats/{objectId}/client/subscriptions");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteClientSubscriptionsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteClientSubscriptionsRequest* UDeleteClientSubscriptionsRequest::Make(FBeamStatsType _ObjectId, FBeamGamerTag _TargetGamerTag, TArray<FString> _Keys, FOptionalBool _bDeleteAll, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteClientSubscriptionsRequest* Req = NewObject<UDeleteClientSubscriptionsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStatClientSubscriptionDeleteRequestBody>(Req);
	Req->Body->TargetGamerTag = _TargetGamerTag;
	Req->Body->Keys = _Keys;
	Req->Body->bDeleteAll = _bDeleteAll;
	

	return Req;
}
