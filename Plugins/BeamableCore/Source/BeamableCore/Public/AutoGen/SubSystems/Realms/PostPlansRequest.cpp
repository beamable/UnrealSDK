
#include "PostPlansRequest.h"

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

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostPlansRequest* UPostPlansRequest::MakePostPlansRequest(FString _Name, FOptionalArrayOfString _MessageBusAnalytics, FString _MemcachedHosts, bool _bMongoSSL, FString _PlatformJBDC, bool _bSharded, FString _MongoHosts, FOptionalArrayOfString _MessageBusCommon, TArray<URedisShardRequestBody*> _RedisShards, UObject* Outer)
{
	UPostPlansRequest* Req = NewObject<UPostPlansRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreatePlanRequestBody>(Req);
	Req->Body->Name = _Name;
	Req->Body->MessageBusAnalytics = _MessageBusAnalytics;
	Req->Body->MemcachedHosts = _MemcachedHosts;
	Req->Body->bMongoSSL = _bMongoSSL;
	Req->Body->PlatformJBDC = _PlatformJBDC;
	Req->Body->bSharded = _bSharded;
	Req->Body->MongoHosts = _MongoHosts;
	Req->Body->MessageBusCommon = _MessageBusCommon;
	Req->Body->RedisShards = _RedisShards;
	

	return Req;
}
