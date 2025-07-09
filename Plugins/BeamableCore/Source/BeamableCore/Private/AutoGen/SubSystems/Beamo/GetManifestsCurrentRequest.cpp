
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetManifestsCurrentRequest.h"

void UGetManifestsCurrentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetManifestsCurrentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/manifests/current");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(bArchived.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("archived"), bArchived.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetManifestsCurrentRequest::BuildBody(FString& BodyString) const
{
	
}

UGetManifestsCurrentRequest* UGetManifestsCurrentRequest::Make(FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetManifestsCurrentRequest* Req = NewObject<UGetManifestsCurrentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->bArchived = _bArchived;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
