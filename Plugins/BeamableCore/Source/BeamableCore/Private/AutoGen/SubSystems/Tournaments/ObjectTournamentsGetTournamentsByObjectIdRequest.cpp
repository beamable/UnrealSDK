
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/ObjectTournamentsGetTournamentsByObjectIdRequest.h"

void UObjectTournamentsGetTournamentsByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectTournamentsGetTournamentsByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/tournaments/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectTournamentsGetTournamentsByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectTournamentsGetTournamentsByObjectIdRequest* UObjectTournamentsGetTournamentsByObjectIdRequest::Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectTournamentsGetTournamentsByObjectIdRequest* Req = NewObject<UObjectTournamentsGetTournamentsByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
