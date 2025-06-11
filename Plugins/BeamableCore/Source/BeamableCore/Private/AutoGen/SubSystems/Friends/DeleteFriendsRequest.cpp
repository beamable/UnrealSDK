
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/DeleteFriendsRequest.h"

void UDeleteFriendsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteFriendsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/social/friends");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteFriendsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteFriendsRequest* UDeleteFriendsRequest::Make(FBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UDeleteFriendsRequest* Req = NewObject<UDeleteFriendsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UPlayerIdRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
