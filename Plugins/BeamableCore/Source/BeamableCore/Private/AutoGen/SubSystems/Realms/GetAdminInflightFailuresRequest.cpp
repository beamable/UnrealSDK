
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetAdminInflightFailuresRequest.h"

void UGetAdminInflightFailuresRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAdminInflightFailuresRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/admin/inflight/failures");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(ServiceObjectId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("serviceObjectId"), *ServiceObjectId.Val);
		bIsFirstQueryParam = false;
	}

	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("serviceName"), *ServiceName);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAdminInflightFailuresRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAdminInflightFailuresRequest* UGetAdminInflightFailuresRequest::Make(FOptionalString _ServiceObjectId, FString _ServiceName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAdminInflightFailuresRequest* Req = NewObject<UGetAdminInflightFailuresRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ServiceObjectId = _ServiceObjectId;
	Req->ServiceName = _ServiceName;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
