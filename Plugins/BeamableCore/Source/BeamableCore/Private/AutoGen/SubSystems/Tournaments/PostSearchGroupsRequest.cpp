
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PostSearchGroupsRequest.h"

void UPostSearchGroupsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSearchGroupsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/search/groups");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSearchGroupsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSearchGroupsRequest* UPostSearchGroupsRequest::Make(FString _ContentId, TArray<int64> _GroupIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSearchGroupsRequest* Req = NewObject<UPostSearchGroupsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetStatusForGroupsRequestBody>(Req);
	Req->Body->ContentId = _ContentId;
	Req->Body->GroupIds = _GroupIds;
	

	return Req;
}
