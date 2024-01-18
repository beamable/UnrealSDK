
#include "BeamableCore/Public/AutoGen/SubSystems/Push/PostSendRequest.h"

void UPostSendRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostSendRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/push/send");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostSendRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostSendRequest* UPostSendRequest::Make(TArray<USendMsg*> _Msgs, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostSendRequest* Req = NewObject<UPostSendRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USendReq>(Req);
	Req->Body->Msgs = _Msgs;
	

	return Req;
}
