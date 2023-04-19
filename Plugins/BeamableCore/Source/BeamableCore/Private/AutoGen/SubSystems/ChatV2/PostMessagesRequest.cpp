
#include "BeamableCore/Public/AutoGen/SubSystems/ChatV2/PostMessagesRequest.h"

void UPostMessagesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostMessagesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/chatV2/{objectId}/messages");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostMessagesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostMessagesRequest* UPostMessagesRequest::Make(int64 _ObjectId, FString _RoomId, FString _Content, UObject* RequestOwner)
{
	UPostMessagesRequest* Req = NewObject<UPostMessagesRequest>(RequestOwner);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USendMessageRequestBody>(Req);
	Req->Body->RoomId = _RoomId;
	Req->Body->Content = _Content;
	

	return Req;
}
