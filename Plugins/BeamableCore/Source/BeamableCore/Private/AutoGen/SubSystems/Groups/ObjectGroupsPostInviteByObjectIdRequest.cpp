
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPostInviteByObjectIdRequest.h"

void UObjectGroupsPostInviteByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectGroupsPostInviteByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/invite");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectGroupsPostInviteByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectGroupsPostInviteByObjectIdRequest* UObjectGroupsPostInviteByObjectIdRequest::Make(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, FOptionalBool _bUseNewRewardsSystem, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectGroupsPostInviteByObjectIdRequest* Req = NewObject<UObjectGroupsPostInviteByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupInvite>(Req);
	Req->Body->GamerTag = _GamerTag;
	Req->Body->SubGroup = _SubGroup;
	Req->Body->bUseNewRewardsSystem = _bUseNewRewardsSystem;
	

	return Req;
}
