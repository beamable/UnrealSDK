
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/DeleteTicketsRequest.h"

void UDeleteTicketsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteTicketsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/matchmaking/tickets/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteTicketsRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteTicketsRequest* UDeleteTicketsRequest::Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteTicketsRequest* Req = NewObject<UDeleteTicketsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
