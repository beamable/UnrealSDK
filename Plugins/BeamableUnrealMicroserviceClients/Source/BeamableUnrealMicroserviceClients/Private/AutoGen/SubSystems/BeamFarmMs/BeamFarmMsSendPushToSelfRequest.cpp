
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendPushToSelfRequest.h"

void UBeamFarmMsSendPushToSelfRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UBeamFarmMsSendPushToSelfRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("micro_BeamFarmMs/SendPushToSelf");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBeamFarmMsSendPushToSelfRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UBeamFarmMsSendPushToSelfRequest* UBeamFarmMsSendPushToSelfRequest::Make(FString _Title, FString _Body, FString _DeepLink, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBeamFarmMsSendPushToSelfRequest* Req = NewObject<UBeamFarmMsSendPushToSelfRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<USendPushToSelfRequestArgs>(Req);
	Req->Body->Title = _Title;
	Req->Body->Body = _Body;
	Req->Body->DeepLink = _DeepLink;
	

	return Req;
}
