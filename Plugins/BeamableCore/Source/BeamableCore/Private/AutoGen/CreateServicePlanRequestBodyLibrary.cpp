
#include "BeamableCore/Public/AutoGen/CreateServicePlanRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateServicePlanRequestBodyLibrary::CreateServicePlanRequestBodyToJsonString(const UCreateServicePlanRequestBody* Serializable, const bool Pretty)
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

UCreateServicePlanRequestBody* UCreateServicePlanRequestBodyLibrary::Make(FString Name, FOptionalBool bMongoSharded, FOptionalBool bMongoTls, FOptionalString MongoHosts, FOptionalString MongoSrvAddress, FOptionalArrayOfRedisShardRequestBody RedisShards, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, UObject* Outer)
{
	auto Serializable = NewObject<UCreateServicePlanRequestBody>(Outer);
	Serializable->Name = Name;
	Serializable->bMongoSharded = bMongoSharded;
	Serializable->bMongoTls = bMongoTls;
	Serializable->MongoHosts = MongoHosts;
	Serializable->MongoSrvAddress = MongoSrvAddress;
	Serializable->RedisShards = RedisShards;
	Serializable->MessageBusAnalytics = MessageBusAnalytics;
	Serializable->MessageBusCommon = MessageBusCommon;
	
	return Serializable;
}

void UCreateServicePlanRequestBodyLibrary::Break(const UCreateServicePlanRequestBody* Serializable, FString& Name, FOptionalBool& bMongoSharded, FOptionalBool& bMongoTls, FOptionalString& MongoHosts, FOptionalString& MongoSrvAddress, FOptionalArrayOfRedisShardRequestBody& RedisShards, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		bMongoSharded = Serializable->bMongoSharded;
		bMongoTls = Serializable->bMongoTls;
		MongoHosts = Serializable->MongoHosts;
		MongoSrvAddress = Serializable->MongoSrvAddress;
		RedisShards = Serializable->RedisShards;
		MessageBusAnalytics = Serializable->MessageBusAnalytics;
		MessageBusCommon = Serializable->MessageBusCommon;
	}
		
}

