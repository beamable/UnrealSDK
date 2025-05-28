
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/ObjectGroupUsersGetSearchByObjectIdRequest.h"

void UObjectGroupUsersGetSearchByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectGroupUsersGetSearchByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/search");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Name.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("name"), *Name.Val);
		bIsFirstQueryParam = false;
	}

	if(ScoreMin.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("scoreMin"), *FString::FromInt(ScoreMin.Val));
		bIsFirstQueryParam = false;
	}

	if(SortField.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("sortField"), *SortField.Val);
		bIsFirstQueryParam = false;
	}

	if(UserScore.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("userScore"), *FString::FromInt(UserScore.Val));
		bIsFirstQueryParam = false;
	}

	if(bHasSlots.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("hasSlots"), bHasSlots.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	if(EnrollmentTypes.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("enrollmentTypes"), *EnrollmentTypes.Val);
		bIsFirstQueryParam = false;
	}

	if(Offset.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("offset"), *FString::FromInt(Offset.Val));
		bIsFirstQueryParam = false;
	}

	if(ScoreMax.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("scoreMax"), *FString::FromInt(ScoreMax.Val));
		bIsFirstQueryParam = false;
	}

	if(bSubGroup.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("subGroup"), bSubGroup.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	if(SortValue.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("sortValue"), *FString::FromInt(SortValue.Val));
		bIsFirstQueryParam = false;
	}

	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("type"), *UBeamJsonUtils::EnumToSerializationName(Type));
	bIsFirstQueryParam = false;
	
	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectGroupUsersGetSearchByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectGroupUsersGetSearchByObjectIdRequest* UObjectGroupUsersGetSearchByObjectIdRequest::Make(int64 _ObjectId, FOptionalString _Name, FOptionalInt64 _ScoreMin, FOptionalString _SortField, FOptionalInt64 _UserScore, FOptionalBool _bHasSlots, FOptionalString _EnrollmentTypes, FOptionalInt32 _Offset, FOptionalInt64 _ScoreMax, FOptionalBool _bSubGroup, FOptionalInt32 _SortValue, EBeamGroupType _Type, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectGroupUsersGetSearchByObjectIdRequest* Req = NewObject<UObjectGroupUsersGetSearchByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Name = _Name;
	Req->ScoreMin = _ScoreMin;
	Req->SortField = _SortField;
	Req->UserScore = _UserScore;
	Req->bHasSlots = _bHasSlots;
	Req->EnrollmentTypes = _EnrollmentTypes;
	Req->Offset = _Offset;
	Req->ScoreMax = _ScoreMax;
	Req->bSubGroup = _bSubGroup;
	Req->SortValue = _SortValue;
	Req->Type = _Type;
	Req->Limit = _Limit;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
