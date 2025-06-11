
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSUpgradeItemRequest.h"

void ULiveOpsDemoMSUpgradeItemRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void ULiveOpsDemoMSUpgradeItemRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_LiveOpsDemoMS/UpgradeItem");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void ULiveOpsDemoMSUpgradeItemRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

ULiveOpsDemoMSUpgradeItemRequest* ULiveOpsDemoMSUpgradeItemRequest::Make(int64 _GamerTag, int64 _ItemInstaceID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	ULiveOpsDemoMSUpgradeItemRequest* Req = NewObject<ULiveOpsDemoMSUpgradeItemRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UUpgradeItemRequestArgs>(Req);
	Req->Body->GamerTag = _GamerTag;
	Req->Body->ItemInstaceID = _ItemInstaceID;
	

	return Req;
}
