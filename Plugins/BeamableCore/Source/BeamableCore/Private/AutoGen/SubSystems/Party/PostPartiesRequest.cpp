
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PostPartiesRequest.h"

void UPostPartiesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPartiesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPartiesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPartiesRequest* UPostPartiesRequest::Make(FOptionalString _Restriction, FOptionalBeamGamerTag _Leader, FOptionalInt32 _MaxSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPartiesRequest* Req = NewObject<UPostPartiesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateParty>(Req);
	Req->Body->Restriction = _Restriction;
	Req->Body->Leader = _Leader;
	Req->Body->MaxSize = _MaxSize;
	

	return Req;
}
