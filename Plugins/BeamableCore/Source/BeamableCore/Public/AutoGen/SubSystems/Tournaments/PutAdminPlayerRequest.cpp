
#include "PutAdminPlayerRequest.h"

void UPutAdminPlayerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutAdminPlayerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/tournaments/admin/player");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutAdminPlayerRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutAdminPlayerRequest* UPutAdminPlayerRequest::MakePutAdminPlayerRequest(int64 _PlayerId, FString _TournamentId, UPlayerStatusUpdate* _Update, UObject* Outer)
{
	UPutAdminPlayerRequest* Req = NewObject<UPutAdminPlayerRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpdatePlayerStatusRequestBody>(Req);
	Req->Body->PlayerId = _PlayerId;
	Req->Body->TournamentId = _TournamentId;
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Update = _Update;
	Req->Body->Update->Rename(nullptr, Req);
	

	return Req;
}
