
#include "PostAnnouncementsRequest.h"

void UPostAnnouncementsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostAnnouncementsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostAnnouncementsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostAnnouncementsRequest* UPostAnnouncementsRequest::MakePostAnnouncementsRequest(ULocalizationRef* _Body, FString _Channel, FOptionalString _StartDate, FOptionalArrayOfString _Tags, FOptionalPlayerReward _Gift, FOptionalArrayOfPlayerStatRequirement _StatRequirements, FString _Symbol, FOptionalMapOfString _ClientData, FOptionalString _EndDate, ULocalizationRef* _Title, FOptionalArrayOfAnnouncementAttachment _Attachments, ULocalizationRef* _Summary, UObject* Outer)
{
	UPostAnnouncementsRequest* Req = NewObject<UPostAnnouncementsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAnnouncementDto>(Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Body = _Body;
	Req->Body->Body->Rename(nullptr, Req);
	Req->Body->Channel = _Channel;
	Req->Body->StartDate = _StartDate;
	Req->Body->Tags = _Tags;
	Req->Body->Gift = _Gift;
	Req->Body->StatRequirements = _StatRequirements;
	Req->Body->Symbol = _Symbol;
	Req->Body->ClientData = _ClientData;
	Req->Body->EndDate = _EndDate;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Title = _Title;
	Req->Body->Title->Rename(nullptr, Req);
	Req->Body->Attachments = _Attachments;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Summary = _Summary;
	Req->Body->Summary->Rename(nullptr, Req);
	

	return Req;
}
