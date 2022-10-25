
#include "AutoGen/SubSystems/Groups/PutDonationsClaimRequest.h"

void UPutDonationsClaimRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutDonationsClaimRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/donations/claim");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutDonationsClaimRequest::BuildBody(FString& BodyString) const
{
	
}

UPutDonationsClaimRequest* UPutDonationsClaimRequest::Make(int64 _ObjectId, UObject* Outer)
{
	UPutDonationsClaimRequest* Req = NewObject<UPutDonationsClaimRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
