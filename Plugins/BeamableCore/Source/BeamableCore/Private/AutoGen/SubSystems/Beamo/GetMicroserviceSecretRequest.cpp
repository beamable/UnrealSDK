
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetMicroserviceSecretRequest.h"

void UGetMicroserviceSecretRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetMicroserviceSecretRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/microservice/secret");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetMicroserviceSecretRequest::BuildBody(FString& BodyString) const
{
	
}

UGetMicroserviceSecretRequest* UGetMicroserviceSecretRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetMicroserviceSecretRequest* Req = NewObject<UGetMicroserviceSecretRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
