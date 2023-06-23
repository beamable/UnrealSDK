
#include "BeamableCore/Public/AutoGen/SubSystems/Match/ApiMatchGetMatchesRequest.h"

void UApiMatchGetMatchesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiMatchGetMatchesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/matchmaking/matches/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiMatchGetMatchesRequest::BuildBody(FString& BodyString) const
{
	
}

UApiMatchGetMatchesRequest* UApiMatchGetMatchesRequest::Make(FGuid _Id, UObject* RequestOwner)
{
	UApiMatchGetMatchesRequest* Req = NewObject<UApiMatchGetMatchesRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
