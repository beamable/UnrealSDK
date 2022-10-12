
#include "BasicAnnouncementsDeleteAnnouncementsRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicAnnouncementsDeleteAnnouncementsRequest* UBasicAnnouncementsDeleteAnnouncementsRequest::MakeBasicAnnouncementsDeleteAnnouncementsRequest(FString _Symbol, UObject* Outer)
{
	UBasicAnnouncementsDeleteAnnouncementsRequest* Req = NewObject<UBasicAnnouncementsDeleteAnnouncementsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteAnnouncementRequestBody>(Req);
	Req->Body->Symbol = _Symbol;
	

	return Req;
}