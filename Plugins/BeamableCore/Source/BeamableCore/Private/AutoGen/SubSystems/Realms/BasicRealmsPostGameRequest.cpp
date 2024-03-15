
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsPostGameRequest.h"

void UBasicRealmsPostGameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBasicRealmsPostGameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/game");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicRealmsPostGameRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBasicRealmsPostGameRequest* UBasicRealmsPostGameRequest::Make(FString _GameName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicRealmsPostGameRequest* Req = NewObject<UBasicRealmsPostGameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UNewGameRequestBody>(Req);
	Req->Body->GameName = _GameName;
	

	return Req;
}
