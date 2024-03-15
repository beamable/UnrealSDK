
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostClientStringlistRequest.h"

void UPostClientStringlistRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostClientStringlistRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/stats/{objectId}/client/stringlist");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostClientStringlistRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostClientStringlistRequest* UPostClientStringlistRequest::Make(FBeamStatsType _ObjectId, FOptionalArrayOfStatStringListEntry _Set, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostClientStringlistRequest* Req = NewObject<UPostClientStringlistRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStatUpdateRequestStringListFormat>(Req);
	Req->Body->Set = _Set;
	

	return Req;
}
