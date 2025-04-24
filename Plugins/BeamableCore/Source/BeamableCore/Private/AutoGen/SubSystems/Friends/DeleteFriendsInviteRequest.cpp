
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/DeleteFriendsInviteRequest.h"

void UDeleteFriendsInviteRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteFriendsInviteRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/friends/invite");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteFriendsInviteRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteFriendsInviteRequest* UDeleteFriendsInviteRequest::Make(FBeamGamerTag _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteFriendsInviteRequest* Req = NewObject<UDeleteFriendsInviteRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USendFriendRequestBody>(Req);
	Req->Body->GamerTag = _GamerTag;
	

	return Req;
}
