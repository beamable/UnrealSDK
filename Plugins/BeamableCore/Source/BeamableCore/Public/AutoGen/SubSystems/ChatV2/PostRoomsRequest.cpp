
#include "PostRoomsRequest.h"

void UPostRoomsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostRoomsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/chatV2/{objectId}/rooms");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostRoomsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostRoomsRequest* UPostRoomsRequest::MakePostRoomsRequest(int64 _ObjectId, FString _RoomName, bool _bKeepSubscribed, TArray<int64> _Players, UObject* Outer)
{
	UPostRoomsRequest* Req = NewObject<UPostRoomsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateRoomRequestBody>(Req);
	Req->Body->RoomName = _RoomName;
	Req->Body->bKeepSubscribed = _bKeepSubscribed;
	Req->Body->Players = _Players;
	

	return Req;
}