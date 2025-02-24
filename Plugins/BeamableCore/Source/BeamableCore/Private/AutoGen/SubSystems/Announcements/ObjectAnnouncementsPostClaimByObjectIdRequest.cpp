
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/ObjectAnnouncementsPostClaimByObjectIdRequest.h"

void UObjectAnnouncementsPostClaimByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UObjectAnnouncementsPostClaimByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/announcements/{objectId}/claim");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectAnnouncementsPostClaimByObjectIdRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UObjectAnnouncementsPostClaimByObjectIdRequest* UObjectAnnouncementsPostClaimByObjectIdRequest::Make(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectAnnouncementsPostClaimByObjectIdRequest* Req = NewObject<UObjectAnnouncementsPostClaimByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAnnouncementRequestBody>(Req);
	Req->Body->Announcement = _Announcement;
	Req->Body->Announcements = _Announcements;
	

	return Req;
}
