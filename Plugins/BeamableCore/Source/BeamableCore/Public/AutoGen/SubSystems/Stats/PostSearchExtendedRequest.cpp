
#include "PostSearchExtendedRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSearchExtendedRequest* UPostSearchExtendedRequest::MakePostSearchExtendedRequest(TArray<UStatsSearchCriteria*> _Criteria, FString _Domain, FString _ObjectType, TArray<FString> _StatKeys, FString _Access, UObject* Outer)
{
	UPostSearchExtendedRequest* Req = NewObject<UPostSearchExtendedRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USearchExtendedRequestBody>(Req);
	Req->Body->Criteria = _Criteria;
	Req->Body->Domain = _Domain;
	Req->Body->ObjectType = _ObjectType;
	Req->Body->StatKeys = _StatKeys;
	Req->Body->Access = _Access;
	

	return Req;
}
