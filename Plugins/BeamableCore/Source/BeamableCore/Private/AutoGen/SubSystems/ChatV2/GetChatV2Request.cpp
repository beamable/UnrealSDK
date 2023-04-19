
#include "BeamableCore/Public/AutoGen/SubSystems/ChatV2/GetChatV2Request.h"

void UGetChatV2Request::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetChatV2Request::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/chatV2/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Scope.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("scope"), *Scope.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetChatV2Request::BuildBody(FString& BodyString) const
{
	
}

UGetChatV2Request* UGetChatV2Request::Make(int64 _ObjectId, FOptionalString _Scope, UObject* RequestOwner)
{
	UGetChatV2Request* Req = NewObject<UGetChatV2Request>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Scope = _Scope;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
