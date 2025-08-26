
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetAliasesRequest.h"

void UGetAliasesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAliasesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/aliases/{alias}");
	Route = Route.Replace(TEXT("{alias}"), *Alias);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAliasesRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAliasesRequest* UGetAliasesRequest::Make(FString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAliasesRequest* Req = NewObject<UGetAliasesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Alias = _Alias;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
