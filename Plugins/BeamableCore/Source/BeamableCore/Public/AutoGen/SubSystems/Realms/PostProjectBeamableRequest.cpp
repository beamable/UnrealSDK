
#include "PostProjectBeamableRequest.h"

void UPostProjectBeamableRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostProjectBeamableRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project/beamable");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostProjectBeamableRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostProjectBeamableRequest* UPostProjectBeamableRequest::MakePostProjectBeamableRequest(FString _Name, FOptionalString _Plan, FOptionalBool _bSharded, FOptionalString _Parent, UObject* Outer)
{
	UPostProjectBeamableRequest* Req = NewObject<UPostProjectBeamableRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateProjectRequestBody>(Req);
	Req->Body->Name = _Name;
	Req->Body->Plan = _Plan;
	Req->Body->bSharded = _bSharded;
	Req->Body->Parent = _Parent;
	

	return Req;
}
