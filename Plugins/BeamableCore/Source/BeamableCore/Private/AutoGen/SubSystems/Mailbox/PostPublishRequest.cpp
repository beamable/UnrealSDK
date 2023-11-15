
#include "BeamableCore/Public/AutoGen/SubSystems/Mailbox/PostPublishRequest.h"

void UPostPublishRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPublishRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/mailbox/publish");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPublishRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPublishRequest* UPostPublishRequest::Make(FOptionalString _Body, FOptionalString _Cid, FOptionalString _Pid, FOptionalString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPublishRequest* Req = NewObject<UPostPublishRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UMessageRequestBody>(Req);
	Req->Body->Body = _Body;
	Req->Body->Cid = _Cid;
	Req->Body->Pid = _Pid;
	Req->Body->PlayerId = _PlayerId;
	

	return Req;
}
