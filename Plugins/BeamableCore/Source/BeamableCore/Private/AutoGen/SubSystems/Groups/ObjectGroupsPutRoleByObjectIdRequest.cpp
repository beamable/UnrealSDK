
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPutRoleByObjectIdRequest.h"

void UObjectGroupsPutRoleByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UObjectGroupsPutRoleByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/role");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectGroupsPutRoleByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectGroupsPutRoleByObjectIdRequest* UObjectGroupsPutRoleByObjectIdRequest::Make(int64 _ObjectId, int64 _GamerTag, FString _Role, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectGroupsPutRoleByObjectIdRequest* Req = NewObject<UObjectGroupsPutRoleByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<URoleChangeRequestBody>(Req);
	Req->Body->GamerTag = _GamerTag;
	Req->Body->Role = _Role;
	Req->Body->SubGroup = _SubGroup;
	

	return Req;
}
