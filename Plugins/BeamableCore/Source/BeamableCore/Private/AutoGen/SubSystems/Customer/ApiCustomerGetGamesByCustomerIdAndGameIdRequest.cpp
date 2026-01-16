
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetGamesByCustomerIdAndGameIdRequest.h"

void UApiCustomerGetGamesByCustomerIdAndGameIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiCustomerGetGamesByCustomerIdAndGameIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/games/{gameId}");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	Route = Route.Replace(TEXT("{gameId}"), *GameId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(bShowHiddenRealms.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("showHiddenRealms"), bShowHiddenRealms.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiCustomerGetGamesByCustomerIdAndGameIdRequest::BuildBody(FString& BodyString) const
{
	
}

UApiCustomerGetGamesByCustomerIdAndGameIdRequest* UApiCustomerGetGamesByCustomerIdAndGameIdRequest::Make(FString _CustomerId, FString _GameId, FOptionalBool _bShowHiddenRealms, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiCustomerGetGamesByCustomerIdAndGameIdRequest* Req = NewObject<UApiCustomerGetGamesByCustomerIdAndGameIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	Req->GameId = _GameId;
	Req->bShowHiddenRealms = _bShowHiddenRealms;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
