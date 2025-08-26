
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutActivateRequest.h"

void UPutActivateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutActivateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/activate");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutActivateRequest::BuildBody(FString& BodyString) const
{
	
}

UPutActivateRequest* UPutActivateRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutActivateRequest* Req = NewObject<UPutActivateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
