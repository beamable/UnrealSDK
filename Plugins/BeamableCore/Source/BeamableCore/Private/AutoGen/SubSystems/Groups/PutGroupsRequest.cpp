
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PutGroupsRequest.h"

void UPutGroupsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutGroupsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutGroupsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutGroupsRequest* UPutGroupsRequest::Make(int64 _ObjectId, FOptionalString _Name, FOptionalString _EnrollmentType, FOptionalString _Tag, FOptionalString _Slogan, FOptionalInt64 _Requirement, FOptionalString _Motd, FOptionalString _ClientData, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutGroupsRequest* Req = NewObject<UPutGroupsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupUpdate>(Req);
	Req->Body->Name = _Name;
	Req->Body->EnrollmentType = _EnrollmentType;
	Req->Body->Tag = _Tag;
	Req->Body->Slogan = _Slogan;
	Req->Body->Requirement = _Requirement;
	Req->Body->Motd = _Motd;
	Req->Body->ClientData = _ClientData;
	Req->Body->SubGroup = _SubGroup;
	

	return Req;
}
