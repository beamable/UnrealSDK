
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/ApiAuthGetTokensByTokenIdRequest.h"

void UApiAuthGetTokensByTokenIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiAuthGetTokensByTokenIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/{tokenId}");
	Route = Route.Replace(TEXT("{tokenId}"), *TokenId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiAuthGetTokensByTokenIdRequest::BuildBody(FString& BodyString) const
{
	
}

UApiAuthGetTokensByTokenIdRequest* UApiAuthGetTokensByTokenIdRequest::Make(FString _TokenId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiAuthGetTokensByTokenIdRequest* Req = NewObject<UApiAuthGetTokensByTokenIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TokenId = _TokenId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
