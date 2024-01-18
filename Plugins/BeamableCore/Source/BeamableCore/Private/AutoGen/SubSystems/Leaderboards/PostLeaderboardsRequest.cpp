
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PostLeaderboardsRequest.h"

void UPostLeaderboardsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostLeaderboardsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostLeaderboardsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostLeaderboardsRequest* UPostLeaderboardsRequest::Make(FString _ObjectId, bool _bSharded, FOptionalBool _bPartitioned, FOptionalInt64 _FreezeTime, FOptionalString _ScoreName, FOptionalLeaderboardCohortSettings _CohortSettings, FOptionalBeamClientPermission _Permissions, FOptionalInt32 _MaxEntries, FOptionalInt64 _Ttl, FOptionalArrayOfString _Derivatives, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostLeaderboardsRequest* Req = NewObject<UPostLeaderboardsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardCreateRequestBody>(Req);
	Req->Body->bSharded = _bSharded;
	Req->Body->bPartitioned = _bPartitioned;
	Req->Body->FreezeTime = _FreezeTime;
	Req->Body->ScoreName = _ScoreName;
	Req->Body->CohortSettings = _CohortSettings;
	Req->Body->Permissions = _Permissions;
	Req->Body->MaxEntries = _MaxEntries;
	Req->Body->Ttl = _Ttl;
	Req->Body->Derivatives = _Derivatives;
	

	return Req;
}
