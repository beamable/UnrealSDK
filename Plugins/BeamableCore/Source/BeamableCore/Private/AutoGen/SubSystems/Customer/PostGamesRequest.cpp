
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostGamesRequest.h"

void UPostGamesRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostGamesRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/customers/{customerId}/games");
	Route = Route.Replace(TEXT("{customerId}"), *CustomerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostGamesRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostGamesRequest* UPostGamesRequest::Make(FString _CustomerId, FString _GameName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostGamesRequest* Req = NewObject<UPostGamesRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->CustomerId = _CustomerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UNewGameRequestBody>(Req);
	Req->Body->GameName = _GameName;
	

	return Req;
}
