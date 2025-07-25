
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/PutOtelViewsRequest.h"

void UPutOtelViewsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutOtelViewsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/otel/views/{viewId}");
	Route = Route.Replace(TEXT("{viewId}"), *ViewId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutOtelViewsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutOtelViewsRequest* UPutOtelViewsRequest::Make(FString _ViewId, FOptionalBool _bIsFavorite, FOptionalBool _bIsPublic, FOptionalString _Name, FOptionalString _Query, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutOtelViewsRequest* Req = NewObject<UPutOtelViewsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ViewId = _ViewId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdateOtelViewRequestBody>(Req);
	Req->Body->bIsFavorite = _bIsFavorite;
	Req->Body->bIsPublic = _bIsPublic;
	Req->Body->Name = _Name;
	Req->Body->Query = _Query;
	

	return Req;
}
