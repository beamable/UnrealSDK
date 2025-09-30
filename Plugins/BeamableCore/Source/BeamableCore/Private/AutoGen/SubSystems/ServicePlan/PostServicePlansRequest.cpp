
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/PostServicePlansRequest.h"

void UPostServicePlansRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostServicePlansRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/service-plans");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostServicePlansRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostServicePlansRequest* UPostServicePlansRequest::Make(FString _Name, FOptionalBool _bMongoSharded, FOptionalBool _bMongoTls, FOptionalString _MongoHosts, FOptionalString _MongoSrvAddress, FOptionalArrayOfRedisShardRequestBody _RedisShards, FOptionalArrayOfString _MessageBusAnalytics, FOptionalArrayOfString _MessageBusCommon, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostServicePlansRequest* Req = NewObject<UPostServicePlansRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateServicePlanRequestBody>(Req);
	Req->Body->Name = _Name;
	Req->Body->bMongoSharded = _bMongoSharded;
	Req->Body->bMongoTls = _bMongoTls;
	Req->Body->MongoHosts = _MongoHosts;
	Req->Body->MongoSrvAddress = _MongoSrvAddress;
	Req->Body->RedisShards = _RedisShards;
	Req->Body->MessageBusAnalytics = _MessageBusAnalytics;
	Req->Body->MessageBusCommon = _MessageBusCommon;
	

	return Req;
}
