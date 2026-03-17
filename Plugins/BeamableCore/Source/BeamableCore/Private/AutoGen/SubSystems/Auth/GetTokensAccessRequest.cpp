
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetTokensAccessRequest.h"

void UGetTokensAccessRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetTokensAccessRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens/access/{tokenId}");
	Route = Route.Replace(TEXT("{tokenId}"), *TokenId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(CustomerId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("customerId"), *CustomerId.Val);
		bIsFirstQueryParam = false;
	}

	if(RealmId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("realmId"), *RealmId.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetTokensAccessRequest::BuildBody(FString& BodyString) const
{
	
}

UGetTokensAccessRequest* UGetTokensAccessRequest::Make(FString _TokenId, FOptionalString _CustomerId, FOptionalString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetTokensAccessRequest* Req = NewObject<UGetTokensAccessRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TokenId = _TokenId;
	Req->CustomerId = _CustomerId;
	Req->RealmId = _RealmId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
