
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/GetServicePlanRequest.h"

void UGetServicePlanRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetServicePlanRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/service-plans/{name}");
	Route = Route.Replace(TEXT("{name}"), *Name);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetServicePlanRequest::BuildBody(FString& BodyString) const
{
	
}

UGetServicePlanRequest* UGetServicePlanRequest::Make(FString _Name, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetServicePlanRequest* Req = NewObject<UGetServicePlanRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Name = _Name;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
