
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetViewRequest.h"

void UGetViewRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetViewRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/leaderboards/{objectId}/view");
	Route = Route.Replace(TEXT("{objectId}"), *ObjectId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Max.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("max"), *FString::FromInt(Max.Val));
		bIsFirstQueryParam = false;
	}

	if(Focus.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("focus"), *FString::FromInt(Focus.Val));
		bIsFirstQueryParam = false;
	}

	if(bFriends.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("friends"), bFriends.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	if(From.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("from"), *FString::FromInt(From.Val));
		bIsFirstQueryParam = false;
	}

	if(Outlier.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("outlier"), *FString::FromInt(Outlier.Val));
		bIsFirstQueryParam = false;
	}

	if(bGuild.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("guild"), bGuild.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetViewRequest::BuildBody(FString& BodyString) const
{
	
}

UGetViewRequest* UGetViewRequest::Make(FString _ObjectId, FOptionalInt32 _Max, FOptionalInt64 _Focus, FOptionalBool _bFriends, FOptionalInt32 _From, FOptionalInt64 _Outlier, FOptionalBool _bGuild, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetViewRequest* Req = NewObject<UGetViewRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Max = _Max;
	Req->Focus = _Focus;
	Req->bFriends = _bFriends;
	Req->From = _From;
	Req->Outlier = _Outlier;
	Req->bGuild = _bGuild;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
