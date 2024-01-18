
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/PostChannelRequest.h"

void UPostChannelRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostChannelRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/notification/channel");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostChannelRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostChannelRequest* UPostChannelRequest::Make(UNotificationRequestData* _Payload, FOptionalBool _bUseSignalWhenPossible, FOptionalString _CustomChannelSuffix, FOptionalInt64 _Dbid, FOptionalArrayOfInt64 _Dbids, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostChannelRequest* Req = NewObject<UPostChannelRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UNotificationRequestBody>(Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Payload = _Payload;
	Req->Body->Payload->Rename(nullptr, Req);
	Req->Body->bUseSignalWhenPossible = _bUseSignalWhenPossible;
	Req->Body->CustomChannelSuffix = _CustomChannelSuffix;
	Req->Body->Dbid = _Dbid;
	Req->Body->Dbids = _Dbids;
	

	return Req;
}
