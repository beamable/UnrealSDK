
#include "BeamableCore/Public/AutoGen/CreatePlanRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreatePlanRequestBodyLibrary::CreatePlanRequestBodyToJsonString(const UCreatePlanRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCreatePlanRequestBody* UCreatePlanRequestBodyLibrary::Make(bool bMongoSSL, bool bSharded, FString Name, FString MemcachedHosts, FString PlatformJBDC, FString MongoHosts, TArray<URedisShardRequestBody*> RedisShards, FOptionalString MongoSrvAddress, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, UObject* Outer)
{
	auto Serializable = NewObject<UCreatePlanRequestBody>(Outer);
	Serializable->bMongoSSL = bMongoSSL;
	Serializable->bSharded = bSharded;
	Serializable->Name = Name;
	Serializable->MemcachedHosts = MemcachedHosts;
	Serializable->PlatformJBDC = PlatformJBDC;
	Serializable->MongoHosts = MongoHosts;
	Serializable->RedisShards = RedisShards;
	Serializable->MongoSrvAddress = MongoSrvAddress;
	Serializable->MessageBusAnalytics = MessageBusAnalytics;
	Serializable->MessageBusCommon = MessageBusCommon;
	
	return Serializable;
}

void UCreatePlanRequestBodyLibrary::Break(const UCreatePlanRequestBody* Serializable, bool& bMongoSSL, bool& bSharded, FString& Name, FString& MemcachedHosts, FString& PlatformJBDC, FString& MongoHosts, TArray<URedisShardRequestBody*>& RedisShards, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bMongoSSL = Serializable->bMongoSSL;
		bSharded = Serializable->bSharded;
		Name = Serializable->Name;
		MemcachedHosts = Serializable->MemcachedHosts;
		PlatformJBDC = Serializable->PlatformJBDC;
		MongoHosts = Serializable->MongoHosts;
		RedisShards = Serializable->RedisShards;
		MongoSrvAddress = Serializable->MongoSrvAddress;
		MessageBusAnalytics = Serializable->MessageBusAnalytics;
		MessageBusCommon = Serializable->MessageBusCommon;
	}
		
}

