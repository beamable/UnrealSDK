
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetLoglevelContextRequest.h"

void UGetLoglevelContextRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetLoglevelContextRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/loglevel-context");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(ServiceName.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("serviceName"), *ServiceName.Val);
		bIsFirstQueryParam = false;
	}

	if(RoutingKey.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("routingKey"), *RoutingKey.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetLoglevelContextRequest::BuildBody(FString& BodyString) const
{
	
}

UGetLoglevelContextRequest* UGetLoglevelContextRequest::Make(FOptionalString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetLoglevelContextRequest* Req = NewObject<UGetLoglevelContextRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	Req->RoutingKey = _RoutingKey;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
