
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostSearchExtendedRequest.h"

void UPostSearchExtendedRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSearchExtendedRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/stats/search/extended");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSearchExtendedRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSearchExtendedRequest* UPostSearchExtendedRequest::Make(FString _Domain, FString _ObjectType, FString _Access, TArray<UStatsSearchCriteria*> _Criteria, TArray<FString> _StatKeys, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSearchExtendedRequest* Req = NewObject<UPostSearchExtendedRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USearchExtendedRequestBody>(Req);
	Req->Body->Domain = _Domain;
	Req->Body->ObjectType = _ObjectType;
	Req->Body->Access = _Access;
	Req->Body->Criteria = _Criteria;
	Req->Body->StatKeys = _StatKeys;
	

	return Req;
}
