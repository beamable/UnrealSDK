
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/PostOtelViewsRequest.h"

void UPostOtelViewsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostOtelViewsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/otel/views");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostOtelViewsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostOtelViewsRequest* UPostOtelViewsRequest::Make(FString _PlayerId, FString _Name, FString _Query, FOptionalBool _bIsFavorite, FOptionalBool _bIsPublic, FOptionalObjectId _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostOtelViewsRequest* Req = NewObject<UPostOtelViewsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UOtelView>(Req);
	Req->Body->PlayerId = _PlayerId;
	Req->Body->Name = _Name;
	Req->Body->Query = _Query;
	Req->Body->bIsFavorite = _bIsFavorite;
	Req->Body->bIsPublic = _bIsPublic;
	Req->Body->Id = _Id;
	

	return Req;
}
