
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetMeGroupRequest.h"

void UGetMeGroupRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetMeGroupRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/me/group");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(ContentId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("contentId"), *ContentId.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetMeGroupRequest::BuildBody(FString& BodyString) const
{
	
}

UGetMeGroupRequest* UGetMeGroupRequest::Make(FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetMeGroupRequest* Req = NewObject<UGetMeGroupRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ContentId = _ContentId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
