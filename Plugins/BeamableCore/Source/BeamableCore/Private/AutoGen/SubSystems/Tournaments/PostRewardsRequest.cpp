
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PostRewardsRequest.h"

void UPostRewardsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostRewardsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/rewards");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostRewardsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostRewardsRequest* UPostRewardsRequest::Make(FOptionalString _TournamentId, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostRewardsRequest* Req = NewObject<UPostRewardsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URewardsRequestBody>(Req);
	Req->Body->TournamentId = _TournamentId;
	Req->Body->ContentId = _ContentId;
	

	return Req;
}
