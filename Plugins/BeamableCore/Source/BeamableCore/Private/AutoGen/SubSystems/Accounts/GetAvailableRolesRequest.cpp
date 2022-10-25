
#include "AutoGen/SubSystems/Accounts/GetAvailableRolesRequest.h"

void UGetAvailableRolesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableRolesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/available-roles");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailableRolesRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableRolesRequest* UGetAvailableRolesRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UGetAvailableRolesRequest* Req = NewObject<UGetAvailableRolesRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
