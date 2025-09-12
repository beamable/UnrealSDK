
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostLoglevelContextRequest.h"

void UPostLoglevelContextRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostLoglevelContextRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/loglevel-context");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostLoglevelContextRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostLoglevelContextRequest* UPostLoglevelContextRequest::Make(FString _ServiceName, FString _RoutingKey, EBeamBeamoV2LogLevel _DefaultLogLevel, FOptionalBeamoV2ObjectId _Id, FOptionalArrayOfBeamoV2LogContextRule _Rules, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostLoglevelContextRequest* Req = NewObject<UPostLoglevelContextRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UBeamoV2LogSwitchContextDocument>(Req);
	Req->Body->ServiceName = _ServiceName;
	Req->Body->RoutingKey = _RoutingKey;
	Req->Body->DefaultLogLevel = _DefaultLogLevel;
	Req->Body->Id = _Id;
	Req->Body->Rules = _Rules;
	

	return Req;
}
