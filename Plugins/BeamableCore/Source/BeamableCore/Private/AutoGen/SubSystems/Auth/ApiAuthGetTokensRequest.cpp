
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/ApiAuthGetTokensRequest.h"

void UApiAuthGetTokensRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiAuthGetTokensRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/auth/tokens");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(PlayerIdOrAccountId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerIdOrAccountId"), *PlayerIdOrAccountId.Val);
		bIsFirstQueryParam = false;
	}

	if(Skip.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("skip"), *FString::FromInt(Skip.Val));
		bIsFirstQueryParam = false;
	}

	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiAuthGetTokensRequest::BuildBody(FString& BodyString) const
{
	
}

UApiAuthGetTokensRequest* UApiAuthGetTokensRequest::Make(FOptionalString _PlayerIdOrAccountId, FOptionalInt32 _Skip, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiAuthGetTokensRequest* Req = NewObject<UApiAuthGetTokensRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerIdOrAccountId = _PlayerIdOrAccountId;
	Req->Skip = _Skip;
	Req->Limit = _Limit;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
