
#include "BeamableCore/Public/AutoGen/SubSystems/Calendars/ObjectCalendarsPostClaimRequest.h"

void UObjectCalendarsPostClaimRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectCalendarsPostClaimRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/calendars/{objectId}/claim");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectCalendarsPostClaimRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectCalendarsPostClaimRequest* UObjectCalendarsPostClaimRequest::Make(int64 _ObjectId, FString _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectCalendarsPostClaimRequest* Req = NewObject<UObjectCalendarsPostClaimRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCalendarClaimRequestBody>(Req);
	Req->Body->Id = _Id;
	

	return Req;
}
