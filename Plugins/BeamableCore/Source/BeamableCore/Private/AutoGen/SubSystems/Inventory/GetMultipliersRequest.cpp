
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetMultipliersRequest.h"

void UGetMultipliersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetMultipliersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/inventory/{objectId}/multipliers");
	Route = Route.Replace(TEXT("{objectId}"), *static_cast<FString>(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetMultipliersRequest::BuildBody(FString& BodyString) const
{
	
}

UGetMultipliersRequest* UGetMultipliersRequest::Make(FBeamGamerTag _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetMultipliersRequest* Req = NewObject<UGetMultipliersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
