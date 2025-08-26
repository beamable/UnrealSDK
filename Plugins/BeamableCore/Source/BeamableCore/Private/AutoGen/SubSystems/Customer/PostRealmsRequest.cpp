
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostRealmsRequest.h"

void UPostRealmsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostRealmsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/realms");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostRealmsRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostRealmsRequest* UPostRealmsRequest::Make(FString _CustomerId, FString _Name, FOptionalBool _bSharded, FOptionalString _Plan, FOptionalString _Parent, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostRealmsRequest* Req = NewObject<UPostRealmsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateRealmRequestBody>(Req);
	Req->Body->Name = _Name;
	Req->Body->bSharded = _bSharded;
	Req->Body->Plan = _Plan;
	Req->Body->Parent = _Parent;
	

	return Req;
}
