
#include "PostGroupRequest.h"

void UPostGroupRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostGroupRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/group");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostGroupRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostGroupRequest* UPostGroupRequest::MakePostGroupRequest(int64 _ObjectId, FString _Name, FString _EnrollmentType, FOptionalString _Tag, int64 _Requirement, FOptionalString _ClientData, FOptionalArrayOfGroupScoreBinding _Scores, FOptionalInt32 _Time, EGroupType _Type, int32 _MaxSize, FOptionalInt64 _Group, UObject* Outer)
{
	UPostGroupRequest* Req = NewObject<UPostGroupRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupCreate>(Req);
	Req->Body->Name = _Name;
	Req->Body->EnrollmentType = _EnrollmentType;
	Req->Body->Tag = _Tag;
	Req->Body->Requirement = _Requirement;
	Req->Body->ClientData = _ClientData;
	Req->Body->Scores = _Scores;
	Req->Body->Time = _Time;
	Req->Body->Type = _Type;
	Req->Body->MaxSize = _MaxSize;
	Req->Body->Group = _Group;
	

	return Req;
}
