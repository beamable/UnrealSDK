
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsGetGroupsByObjectIdRequest.h"

void UObjectGroupsGetGroupsByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectGroupsGetGroupsByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectGroupsGetGroupsByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectGroupsGetGroupsByObjectIdRequest* UObjectGroupsGetGroupsByObjectIdRequest::Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectGroupsGetGroupsByObjectIdRequest* Req = NewObject<UObjectGroupsGetGroupsByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
