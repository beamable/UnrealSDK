
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteServicesLogsQueryRequest.h"

void UDeleteServicesLogsQueryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteServicesLogsQueryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/services/logs/query/{queryId}");
	Route = Route.Replace(TEXT("{queryId}"), *QueryId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteServicesLogsQueryRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteServicesLogsQueryRequest* UDeleteServicesLogsQueryRequest::Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteServicesLogsQueryRequest* Req = NewObject<UDeleteServicesLogsQueryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->QueryId = _QueryId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
