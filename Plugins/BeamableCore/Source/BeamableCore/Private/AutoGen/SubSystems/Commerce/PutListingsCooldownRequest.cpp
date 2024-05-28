
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PutListingsCooldownRequest.h"

void UPutListingsCooldownRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutListingsCooldownRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/listings/cooldown");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutListingsCooldownRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutListingsCooldownRequest* UPutListingsCooldownRequest::Make(int64 _ObjectId, int64 _GamerTag, TArray<UUpdateListingCooldownRequestBody*> _UpdateListingCooldownRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutListingsCooldownRequest* Req = NewObject<UPutListingsCooldownRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCooldownModifierRequestBody>(Req);
	Req->Body->GamerTag = _GamerTag;
	Req->Body->UpdateListingCooldownRequests = _UpdateListingCooldownRequests;
	

	return Req;
}
