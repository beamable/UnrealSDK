
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetGetPersonallyIdentifiableInformationRequest.h"

void UGetGetPersonallyIdentifiableInformationRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetGetPersonallyIdentifiableInformationRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/get-personally-identifiable-information");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("query"), *Query);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetGetPersonallyIdentifiableInformationRequest::BuildBody(FString& BodyString) const
{
	
}

UGetGetPersonallyIdentifiableInformationRequest* UGetGetPersonallyIdentifiableInformationRequest::Make(FString _Query, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetGetPersonallyIdentifiableInformationRequest* Req = NewObject<UGetGetPersonallyIdentifiableInformationRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Query = _Query;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
