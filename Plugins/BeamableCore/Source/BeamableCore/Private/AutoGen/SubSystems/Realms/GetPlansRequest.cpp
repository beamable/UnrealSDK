
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetPlansRequest.h"

void UGetPlansRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetPlansRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/plans");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetPlansRequest::BuildBody(FString& BodyString) const
{
	
}

UGetPlansRequest* UGetPlansRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetPlansRequest* Req = NewObject<UGetPlansRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
