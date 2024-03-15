
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostLaunchMessageRequest.h"

void UPostLaunchMessageRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostLaunchMessageRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/launch-message");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostLaunchMessageRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostLaunchMessageRequest* UPostLaunchMessageRequest::Make(FString _Name, FString _Body, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostLaunchMessageRequest* Req = NewObject<UPostLaunchMessageRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateLaunchMessageRequestBody>(Req);
	Req->Body->Name = _Name;
	Req->Body->Body = _Body;
	

	return Req;
}
