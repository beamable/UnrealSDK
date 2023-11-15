
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/GetTicketsRequest.h"

void UGetTicketsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetTicketsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/matchmaking/tickets/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetTicketsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetTicketsRequest* UGetTicketsRequest::Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetTicketsRequest* Req = NewObject<UGetTicketsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
