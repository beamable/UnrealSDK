
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableRolesRequest.h"

void UGetAvailableRolesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableRolesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/available-roles");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailableRolesRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableRolesRequest* UGetAvailableRolesRequest::Make(FBeamAccountId _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAvailableRolesRequest* Req = NewObject<UGetAvailableRolesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
