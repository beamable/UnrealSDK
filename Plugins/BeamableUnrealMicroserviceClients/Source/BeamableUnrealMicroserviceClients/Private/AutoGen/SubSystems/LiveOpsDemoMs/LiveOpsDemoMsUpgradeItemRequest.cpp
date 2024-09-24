
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsUpgradeItemRequest.h"

void ULiveOpsDemoMsUpgradeItemRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMsUpgradeItemRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("_microLiveOpsDemoMs/UpgradeItem");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMsUpgradeItemRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMsUpgradeItemRequest* ULiveOpsDemoMsUpgradeItemRequest::Make(int64 _UserID, int64 _ItemInstaceID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMsUpgradeItemRequest* Req = NewObject<ULiveOpsDemoMsUpgradeItemRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpgradeItemRequestArgs>(Req);
	Req->Body->UserID = _UserID;
	Req->Body->ItemInstaceID = _ItemInstaceID;
	

	return Req;
}
