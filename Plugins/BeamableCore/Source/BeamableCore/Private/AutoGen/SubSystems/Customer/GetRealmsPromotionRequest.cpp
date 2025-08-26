
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetRealmsPromotionRequest.h"

void UGetRealmsPromotionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetRealmsPromotionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/realms/{destinationRealmId}/promotion");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	Route = Route.Replace(TEXT("{destinationRealmId}"), *DestinationRealmId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(SourceRealmId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("sourceRealmId"), *SourceRealmId.Val);
		bIsFirstQueryParam = false;
	}

	if(Promotables.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("promotables"), *Promotables.Val);
		bIsFirstQueryParam = false;
	}

	if(ContentIds.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("contentIds"), *ContentIds.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetRealmsPromotionRequest::BuildBody(FString& BodyString) const
{
	
}

UGetRealmsPromotionRequest* UGetRealmsPromotionRequest::Make(FString _CustomerId, FString _DestinationRealmId, FOptionalString _SourceRealmId, FOptionalString _Promotables, FOptionalString _ContentIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetRealmsPromotionRequest* Req = NewObject<UGetRealmsPromotionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	Req->DestinationRealmId = _DestinationRealmId;
	Req->SourceRealmId = _SourceRealmId;
	Req->Promotables = _Promotables;
	Req->ContentIds = _ContentIds;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
