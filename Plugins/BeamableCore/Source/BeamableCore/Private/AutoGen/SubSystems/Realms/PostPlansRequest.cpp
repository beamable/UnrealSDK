
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostPlansRequest.h"

void UPostPlansRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostPlansRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/plans");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostPlansRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPlansRequest* UPostPlansRequest::Make(bool _bMongoSSL, bool _bSharded, FString _Name, FString _MemcachedHosts, FString _PlatformJBDC, FString _MongoHosts, TArray<URedisShardRequestBody*> _RedisShards, FOptionalString _MongoSrvAddress, FOptionalArrayOfString _MessageBusAnalytics, FOptionalArrayOfString _MessageBusCommon, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostPlansRequest* Req = NewObject<UPostPlansRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreatePlanRequestBody>(Req);
	Req->Body->bMongoSSL = _bMongoSSL;
	Req->Body->bSharded = _bSharded;
	Req->Body->Name = _Name;
	Req->Body->MemcachedHosts = _MemcachedHosts;
	Req->Body->PlatformJBDC = _PlatformJBDC;
	Req->Body->MongoHosts = _MongoHosts;
	Req->Body->RedisShards = _RedisShards;
	Req->Body->MongoSrvAddress = _MongoSrvAddress;
	Req->Body->MessageBusAnalytics = _MessageBusAnalytics;
	Req->Body->MessageBusCommon = _MessageBusCommon;
	

	return Req;
}
