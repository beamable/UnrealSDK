
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/PostFriendsMakeRequest.h"

void UPostFriendsMakeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostFriendsMakeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/friends/make");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostFriendsMakeRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostFriendsMakeRequest* UPostFriendsMakeRequest::Make(FBeamGamerTag _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostFriendsMakeRequest* Req = NewObject<UPostFriendsMakeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMakeFriendshipRequestBody>(Req);
	Req->Body->GamerTag = _GamerTag;
	

	return Req;
}
