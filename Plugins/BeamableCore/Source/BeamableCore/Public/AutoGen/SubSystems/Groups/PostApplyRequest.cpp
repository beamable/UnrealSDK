
#include "PostApplyRequest.h"

void UPostApplyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostApplyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/groups/{objectId}/apply");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostApplyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostApplyRequest* UPostApplyRequest::MakePostApplyRequest(int64 _ObjectId, FOptionalInt64 _SubGroup, UObject* Outer)
{
	UPostApplyRequest* Req = NewObject<UPostApplyRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UGroupApplication>(Req);
	Req->Body->SubGroup = _SubGroup;
	

	return Req;
}