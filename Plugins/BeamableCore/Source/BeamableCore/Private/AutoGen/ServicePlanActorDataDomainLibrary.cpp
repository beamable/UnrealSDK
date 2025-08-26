
#include "BeamableCore/Public/AutoGen/ServicePlanActorDataDomainLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlanActorDataDomainLibrary::ServicePlanActorDataDomainToJsonString(const UServicePlanActorDataDomain* Serializable, const bool Pretty)
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

UServicePlanActorDataDomain* UServicePlanActorDataDomainLibrary::Make(FOptionalBool bMongoSharded, FOptionalBool bMongoTls, FOptionalString MongoSrvAddress, FOptionalArrayOfString MongoHosts, FOptionalArrayOfString MessageBusCommon, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfRedisShard RedisShards, UObject* Outer)
{
	auto Serializable = NewObject<UServicePlanActorDataDomain>(Outer);
	Serializable->bMongoSharded = bMongoSharded;
	Serializable->bMongoTls = bMongoTls;
	Serializable->MongoSrvAddress = MongoSrvAddress;
	Serializable->MongoHosts = MongoHosts;
	Serializable->MessageBusCommon = MessageBusCommon;
	Serializable->MessageBusAnalytics = MessageBusAnalytics;
	Serializable->RedisShards = RedisShards;
	
	return Serializable;
}

void UServicePlanActorDataDomainLibrary::Break(const UServicePlanActorDataDomain* Serializable, FOptionalBool& bMongoSharded, FOptionalBool& bMongoTls, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MongoHosts, FOptionalArrayOfString& MessageBusCommon, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfRedisShard& RedisShards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bMongoSharded = Serializable->bMongoSharded;
		bMongoTls = Serializable->bMongoTls;
		MongoSrvAddress = Serializable->MongoSrvAddress;
		MongoHosts = Serializable->MongoHosts;
		MessageBusCommon = Serializable->MessageBusCommon;
		MessageBusAnalytics = Serializable->MessageBusAnalytics;
		RedisShards = Serializable->RedisShards;
	}
		
}

