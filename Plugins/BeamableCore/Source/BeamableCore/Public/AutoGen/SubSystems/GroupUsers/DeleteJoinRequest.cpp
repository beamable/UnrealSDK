
#include "DeleteJoinRequest.h"

void UDeleteJoinRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteJoinRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/join");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteJoinRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteJoinRequest* UDeleteJoinRequest::MakeDeleteJoinRequest(int64 _ObjectId, FOptionalInt64 _Successor, FOptionalInt64 _Score, FOptionalInt64 _SubGroup, EGroupType _Type, int64 _Group, UObject* Outer)
{
	UDeleteJoinRequest* Req = NewObject<UDeleteJoinRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupMembershipRequestBody>(Req);
	Req->Body->Successor = _Successor;
	Req->Body->Score = _Score;
	Req->Body->SubGroup = _SubGroup;
	Req->Body->Type = _Type;
	Req->Body->Group = _Group;
	

	return Req;
}