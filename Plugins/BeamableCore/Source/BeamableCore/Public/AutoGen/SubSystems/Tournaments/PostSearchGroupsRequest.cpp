
#include "PostSearchGroupsRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSearchGroupsRequest* UPostSearchGroupsRequest::MakePostSearchGroupsRequest(TArray<int64> _GroupIds, FString _ContentId, UObject* Outer)
{
	UPostSearchGroupsRequest* Req = NewObject<UPostSearchGroupsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGetStatusForGroupsRequestBody>(Req);
	Req->Body->GroupIds = _GroupIds;
	Req->Body->ContentId = _ContentId;
	

	return Req;
}
