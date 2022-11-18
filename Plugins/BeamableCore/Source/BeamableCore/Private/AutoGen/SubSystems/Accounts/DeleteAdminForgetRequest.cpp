
#include "AutoGen/SubSystems/Accounts/DeleteAdminForgetRequest.h"

void UDeleteAdminForgetRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteAdminForgetRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/accounts/{objectId}/admin/forget");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteAdminForgetRequest::BuildBody(FString& BodyString) const
{
	
}

UDeleteAdminForgetRequest* UDeleteAdminForgetRequest::Make(int64 _ObjectId, UObject* RequestOwner)
{
	UDeleteAdminForgetRequest* Req = NewObject<UDeleteAdminForgetRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
