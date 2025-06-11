
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/PostJoinRequest.h"

void UPostJoinRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostJoinRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/join");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostJoinRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostJoinRequest* UPostJoinRequest::Make(int64 _ObjectId, EBeamGroupType _Type, int64 _Group, FOptionalInt64 _Successor, FOptionalInt64 _Score, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostJoinRequest* Req = NewObject<UPostJoinRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupMembershipRequestBody>(Req);
	Req->Body->Type = _Type;
	Req->Body->Group = _Group;
	Req->Body->Successor = _Successor;
	Req->Body->Score = _Score;
	Req->Body->SubGroup = _SubGroup;
	

	return Req;
}
