
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPutRoleRequest.h"

void UObjectGroupsPutRoleRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UObjectGroupsPutRoleRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/role");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectGroupsPutRoleRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectGroupsPutRoleRequest* UObjectGroupsPutRoleRequest::Make(int64 _ObjectId, int64 _GamerTag, FString _Role, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectGroupsPutRoleRequest* Req = NewObject<UObjectGroupsPutRoleRequest>(RequestOwner);
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
