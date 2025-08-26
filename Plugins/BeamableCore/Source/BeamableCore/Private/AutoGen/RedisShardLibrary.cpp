
#include "BeamableCore/Public/AutoGen/RedisShardLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URedisShardLibrary::RedisShardToJsonString(const URedisShard* Serializable, const bool Pretty)
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

URedisShard* URedisShardLibrary::Make(FOptionalInt32 ShardId, FOptionalString MasterHost, FOptionalArrayOfString SlaveHosts, UObject* Outer)
{
	auto Serializable = NewObject<URedisShard>(Outer);
	Serializable->ShardId = ShardId;
	Serializable->MasterHost = MasterHost;
	Serializable->SlaveHosts = SlaveHosts;
	
	return Serializable;
}

void URedisShardLibrary::Break(const URedisShard* Serializable, FOptionalInt32& ShardId, FOptionalString& MasterHost, FOptionalArrayOfString& SlaveHosts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ShardId = Serializable->ShardId;
		MasterHost = Serializable->MasterHost;
		SlaveHosts = Serializable->SlaveHosts;
	}
		
}

