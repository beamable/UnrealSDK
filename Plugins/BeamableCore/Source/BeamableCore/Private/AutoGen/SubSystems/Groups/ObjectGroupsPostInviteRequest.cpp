
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPostInviteRequest.h"

void UObjectGroupsPostInviteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectGroupsPostInviteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/invite");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectGroupsPostInviteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectGroupsPostInviteRequest* UObjectGroupsPostInviteRequest::Make(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, FOptionalBool _bUseNewRewardsSystem, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectGroupsPostInviteRequest* Req = NewObject<UObjectGroupsPostInviteRequest>(RequestOwner);
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
