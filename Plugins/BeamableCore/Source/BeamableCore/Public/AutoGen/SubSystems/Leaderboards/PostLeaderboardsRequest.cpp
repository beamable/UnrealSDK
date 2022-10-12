
#include "PostLeaderboardsRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostLeaderboardsRequest* UPostLeaderboardsRequest::MakePostLeaderboardsRequest(FString _ObjectId, FOptionalInt64 _FreezeTime, FOptionalArrayOfString _Derivatives, FOptionalString _ScoreName, FOptionalLeaderboardCohortSettings _CohortSettings, FOptionalClientPermission _Permissions, FOptionalInt32 _MaxEntries, FOptionalBool _bPartitioned, bool _bSharded, FOptionalInt64 _Ttl, UObject* Outer)
{
	UPostLeaderboardsRequest* Req = NewObject<UPostLeaderboardsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<ULeaderboardCreateRequestBody>(Req);
	Req->Body->FreezeTime = _FreezeTime;
	Req->Body->Derivatives = _Derivatives;
	Req->Body->ScoreName = _ScoreName;
	Req->Body->CohortSettings = _CohortSettings;
	Req->Body->Permissions = _Permissions;
	Req->Body->MaxEntries = _MaxEntries;
	Req->Body->bPartitioned = _bPartitioned;
	Req->Body->bSharded = _bSharded;
	Req->Body->Ttl = _Ttl;
	

	return Req;
}
