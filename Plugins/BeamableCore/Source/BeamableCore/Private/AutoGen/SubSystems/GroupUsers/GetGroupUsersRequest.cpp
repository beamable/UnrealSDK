
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/GetGroupUsersRequest.h"

void UGetGroupUsersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetGroupUsersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetGroupUsersRequest::BuildBody(FString& BodyString) const
{
	
}

UGetGroupUsersRequest* UGetGroupUsersRequest::Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetGroupUsersRequest* Req = NewObject<UGetGroupUsersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
