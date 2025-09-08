
#include "BeamableCore/Public/AutoGen/SubSystems/Admin/GetInflightFailuresRequest.h"

void UGetInflightFailuresRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetInflightFailuresRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/admin/inflight/failures");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(ServiceName.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("serviceName"), *ServiceName.Val);
		bIsFirstQueryParam = false;
	}

	if(ServiceObjectId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("serviceObjectId"), *ServiceObjectId.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetInflightFailuresRequest::BuildBody(FString& BodyString) const
{
	
}

UGetInflightFailuresRequest* UGetInflightFailuresRequest::Make(FOptionalString _ServiceName, FOptionalString _ServiceObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetInflightFailuresRequest* Req = NewObject<UGetInflightFailuresRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceName = _ServiceName;
	Req->ServiceObjectId = _ServiceObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
