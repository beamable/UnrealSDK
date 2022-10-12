
#include "PostFriendsMakeRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostFriendsMakeRequest* UPostFriendsMakeRequest::MakePostFriendsMakeRequest(int64 _GamerTag, UObject* Outer)
{
	UPostFriendsMakeRequest* Req = NewObject<UPostFriendsMakeRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMakeFriendshipRequestBody>(Req);
	Req->Body->GamerTag = _GamerTag;
	

	return Req;
}
