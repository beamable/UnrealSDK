
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/GetServicePlansRequest.h"

void UGetServicePlansRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetServicePlansRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/service-plans");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetServicePlansRequest::BuildBody(FString& BodyString) const
{
	
}

UGetServicePlansRequest* UGetServicePlansRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetServicePlansRequest* Req = NewObject<UGetServicePlansRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
