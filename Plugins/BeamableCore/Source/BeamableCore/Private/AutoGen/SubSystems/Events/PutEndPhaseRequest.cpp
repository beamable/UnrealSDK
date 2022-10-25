
#include "AutoGen/SubSystems/Events/PutEndPhaseRequest.h"

void UPutEndPhaseRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutEndPhaseRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/events/{objectId}/endPhase");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutEndPhaseRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutEndPhaseRequest* UPutEndPhaseRequest::Make(int64 _ObjectId, FOptionalString _Time, UObject* Outer)
{
	UPutEndPhaseRequest* Req = NewObject<UPutEndPhaseRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEventPhaseEndRequestBody>(Req);
	Req->Body->Time = _Time;
	

	return Req;
}
