
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/PostAnnouncementsRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostAnnouncementsRequest* UPostAnnouncementsRequest::Make(ULocalizationRef* _Body, FString _Channel, FString _Symbol, ULocalizationRef* _Title, ULocalizationRef* _Summary, FOptionalString _StartDate, FOptionalPlayerReward _Gift, FOptionalString _EndDate, FOptionalArrayOfString _Tags, FOptionalArrayOfPlayerStatRequirement _StatRequirements, FOptionalArrayOfAnnouncementAttachment _Attachments, FOptionalMapOfString _ClientData, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostAnnouncementsRequest* Req = NewObject<UPostAnnouncementsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UAnnouncementDto>(Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Body = _Body;
	Req->Body->Body->Rename(nullptr, Req);
	Req->Body->Channel = _Channel;
	Req->Body->Symbol = _Symbol;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Title = _Title;
	Req->Body->Title->Rename(nullptr, Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Summary = _Summary;
	Req->Body->Summary->Rename(nullptr, Req);
	Req->Body->StartDate = _StartDate;
	Req->Body->Gift = _Gift;
	Req->Body->EndDate = _EndDate;
	Req->Body->Tags = _Tags;
	Req->Body->StatRequirements = _StatRequirements;
	Req->Body->Attachments = _Attachments;
	Req->Body->ClientData = _ClientData;
	

	return Req;
}
