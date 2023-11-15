
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetRoleReportRequest.h"

void UGetRoleReportRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRoleReportRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/role/report");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRoleReportRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRoleReportRequest* UGetRoleReportRequest::Make(FBeamAccountId _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRoleReportRequest* Req = NewObject<UGetRoleReportRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
