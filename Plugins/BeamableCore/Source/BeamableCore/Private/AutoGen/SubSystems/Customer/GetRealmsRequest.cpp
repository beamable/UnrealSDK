
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetRealmsRequest.h"

void UGetRealmsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRealmsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/realms/{realmId}");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	Route = Route.Replace(TEXT("{realmId}"), *RealmId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRealmsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRealmsRequest* UGetRealmsRequest::Make(FString _CustomerId, FString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRealmsRequest* Req = NewObject<UGetRealmsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	Req->RealmId = _RealmId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
