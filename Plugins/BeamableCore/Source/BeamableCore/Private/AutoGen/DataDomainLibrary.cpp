
#include "BeamableCore/Public/AutoGen/DataDomainLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDataDomainLibrary::DataDomainToJsonString(const UDataDomain* Serializable, const bool Pretty)
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

UDataDomain* UDataDomainLibrary::Make(bool bMongoSSLEnabled, bool bMongoSharded, TArray<FString> MemcachedHosts, TArray<FString> MongoHosts, FOptionalBool bMongoSSL, FOptionalString MongoSrvAddress, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, FOptionalArrayOfRedisShard RedisShards, UObject* Outer)
{
	auto Serializable = NewObject<UDataDomain>(Outer);
	Serializable->bMongoSSLEnabled = bMongoSSLEnabled;
	Serializable->bMongoSharded = bMongoSharded;
	Serializable->MemcachedHosts = MemcachedHosts;
	Serializable->MongoHosts = MongoHosts;
	Serializable->bMongoSSL = bMongoSSL;
	Serializable->MongoSrvAddress = MongoSrvAddress;
	Serializable->MessageBusAnalytics = MessageBusAnalytics;
	Serializable->MessageBusCommon = MessageBusCommon;
	Serializable->RedisShards = RedisShards;
	
	return Serializable;
}

void UDataDomainLibrary::Break(const UDataDomain* Serializable, bool& bMongoSSLEnabled, bool& bMongoSharded, TArray<FString>& MemcachedHosts, TArray<FString>& MongoHosts, FOptionalBool& bMongoSSL, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon, FOptionalArrayOfRedisShard& RedisShards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bMongoSSLEnabled = Serializable->bMongoSSLEnabled;
		bMongoSharded = Serializable->bMongoSharded;
		MemcachedHosts = Serializable->MemcachedHosts;
		MongoHosts = Serializable->MongoHosts;
		bMongoSSL = Serializable->bMongoSSL;
		MongoSrvAddress = Serializable->MongoSrvAddress;
		MessageBusAnalytics = Serializable->MessageBusAnalytics;
		MessageBusCommon = Serializable->MessageBusCommon;
		RedisShards = Serializable->RedisShards;
	}
		
}

