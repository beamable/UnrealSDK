
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/BasicAnnouncementsDeleteAnnouncementsRequest.h"

void UBasicAnnouncementsDeleteAnnouncementsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UBasicAnnouncementsDeleteAnnouncementsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicAnnouncementsDeleteAnnouncementsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicAnnouncementsDeleteAnnouncementsRequest* UBasicAnnouncementsDeleteAnnouncementsRequest::Make(FString _Symbol, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicAnnouncementsDeleteAnnouncementsRequest* Req = NewObject<UBasicAnnouncementsDeleteAnnouncementsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteAnnouncementRequestBody>(Req);
	Req->Body->Symbol = _Symbol;
	

	return Req;
}
