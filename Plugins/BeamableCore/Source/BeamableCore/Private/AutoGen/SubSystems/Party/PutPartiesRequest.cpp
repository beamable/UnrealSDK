
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPartiesRequest.h"

void UPutPartiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPartiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPartiesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPutPartiesRequest* UPutPartiesRequest::Make(FOptionalString _Id, FOptionalString _Restriction, FOptionalBeamGamerTag _Leader, FOptionalInt32 _MaxSize, FOptionalDateTime _Created, FOptionalArrayOfBeamGamerTag _Members, FOptionalArrayOfString _PendingInvites, FOptionalMapOfTagList _MembersTags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPartiesRequest* Req = NewObject<UPutPartiesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UParty>(Req);
	Req->Body->Id = _Id;
	Req->Body->Restriction = _Restriction;
	Req->Body->Leader = _Leader;
	Req->Body->MaxSize = _MaxSize;
	Req->Body->Created = _Created;
	Req->Body->Members = _Members;
	Req->Body->PendingInvites = _PendingInvites;
	Req->Body->MembersTags = _MembersTags;
	

	return Req;
}
