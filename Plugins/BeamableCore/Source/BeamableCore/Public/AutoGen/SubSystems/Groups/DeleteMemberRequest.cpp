
#include "DeleteMemberRequest.h"

void UDeleteMemberRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteMemberRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/member");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteMemberRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteMemberRequest* UDeleteMemberRequest::MakeDeleteMemberRequest(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, UObject* Outer)
{
	UDeleteMemberRequest* Req = NewObject<UDeleteMemberRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UKickRequestBody>(Req);
	Req->Body->GamerTag = _GamerTag;
	Req->Body->SubGroup = _SubGroup;
	

	return Req;
}