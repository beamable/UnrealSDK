
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetInventoryRequest.h"

void UGetInventoryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetInventoryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Scope.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("scope"), *Scope.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetInventoryRequest::BuildBody(FString& BodyString) const
{
	
}

UGetInventoryRequest* UGetInventoryRequest::Make(FBeamGamerTag _ObjectId, FOptionalString _Scope, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetInventoryRequest* Req = NewObject<UGetInventoryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Scope = _Scope;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
