
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/BasicStatsPostSearchRequest.h"

void UBasicStatsPostSearchRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBasicStatsPostSearchRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/stats/search");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicStatsPostSearchRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicStatsPostSearchRequest* UBasicStatsPostSearchRequest::Make(FString _Domain, FString _Access, FString _ObjectType, TArray<UStatsSearchCriteria*> _Criteria, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicStatsPostSearchRequest* Req = NewObject<UBasicStatsPostSearchRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UStatsSearchRequestBody>(Req);
	Req->Body->Domain = _Domain;
	Req->Body->Access = _Access;
	Req->Body->ObjectType = _ObjectType;
	Req->Body->Criteria = _Criteria;
	

	return Req;
}
