
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetAuditsRequest.h"

void UGetAuditsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAuditsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/audits");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Providerid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("providerid"), *Providerid.Val);
		bIsFirstQueryParam = false;
	}

	if(Provider.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("provider"), *Provider.Val);
		bIsFirstQueryParam = false;
	}

	if(State.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("state"), *State.Val);
		bIsFirstQueryParam = false;
	}

	if(Txid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("txid"), *FString::FromInt(Txid.Val));
		bIsFirstQueryParam = false;
	}

	if(Player.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("player"), *FString::FromInt(Player.Val));
		bIsFirstQueryParam = false;
	}

	if(Start.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("start"), *FString::FromInt(Start.Val));
		bIsFirstQueryParam = false;
	}

	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAuditsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAuditsRequest* UGetAuditsRequest::Make(FOptionalString _Providerid, FOptionalString _Provider, FOptionalString _State, FOptionalInt64 _Txid, FOptionalInt64 _Player, FOptionalInt32 _Start, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAuditsRequest* Req = NewObject<UGetAuditsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Providerid = _Providerid;
	Req->Provider = _Provider;
	Req->State = _State;
	Req->Txid = _Txid;
	Req->Player = _Player;
	Req->Start = _Start;
	Req->Limit = _Limit;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
