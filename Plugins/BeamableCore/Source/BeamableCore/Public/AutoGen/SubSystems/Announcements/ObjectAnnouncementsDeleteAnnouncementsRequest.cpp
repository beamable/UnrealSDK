
#include "ObjectAnnouncementsDeleteAnnouncementsRequest.h"

void UObjectAnnouncementsDeleteAnnouncementsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UObjectAnnouncementsDeleteAnnouncementsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/announcements/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectAnnouncementsDeleteAnnouncementsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectAnnouncementsDeleteAnnouncementsRequest* UObjectAnnouncementsDeleteAnnouncementsRequest::MakeObjectAnnouncementsDeleteAnnouncementsRequest(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* Outer)
{
	UObjectAnnouncementsDeleteAnnouncementsRequest* Req = NewObject<UObjectAnnouncementsDeleteAnnouncementsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAnnouncementRequestBody>(Req);
	Req->Body->Announcement = _Announcement;
	Req->Body->Announcements = _Announcements;
	

	return Req;
}
