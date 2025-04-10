
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeletePartiesRequest.h"

void UDeletePartiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeletePartiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/players/{playerId}/parties");
	Route = Route.Replace(TEXT("{playerId}"), *PlayerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeletePartiesRequest::BuildBody(FString& BodyString) const
{
	
}

UDeletePartiesRequest* UDeletePartiesRequest::Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeletePartiesRequest* Req = NewObject<UDeletePartiesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
