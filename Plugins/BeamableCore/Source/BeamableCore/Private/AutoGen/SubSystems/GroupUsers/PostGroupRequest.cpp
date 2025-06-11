
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/PostGroupRequest.h"

void UPostGroupRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostGroupRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/group");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostGroupRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostGroupRequest* UPostGroupRequest::Make(int64 _ObjectId, FString _Name, FString _EnrollmentType, int64 _Requirement, EBeamGroupType _Type, int32 _MaxSize, FOptionalString _Tag, FOptionalString _ClientData, FOptionalInt64 _Time, FOptionalInt64 _Group, FOptionalArrayOfGroupScoreBinding _Scores, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostGroupRequest* Req = NewObject<UPostGroupRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupCreate>(Req);
	Req->Body->Name = _Name;
	Req->Body->EnrollmentType = _EnrollmentType;
	Req->Body->Requirement = _Requirement;
	Req->Body->Type = _Type;
	Req->Body->MaxSize = _MaxSize;
	Req->Body->Tag = _Tag;
	Req->Body->ClientData = _ClientData;
	Req->Body->Time = _Time;
	Req->Body->Group = _Group;
	Req->Body->Scores = _Scores;
	

	return Req;
}
