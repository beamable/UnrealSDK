
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetCustomersRequest.h"

void UGetCustomersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetCustomersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customers");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetCustomersRequest::BuildBody(FString& BodyString) const
{
	
}

UGetCustomersRequest* UGetCustomersRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetCustomersRequest* Req = NewObject<UGetCustomersRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
