
#include "BeamableCore/Public/AutoGen/RedisShardRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URedisShardRequestBodyLibrary::RedisShardRequestBodyToJsonString(const URedisShardRequestBody* Serializable, const bool Pretty)
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

URedisShardRequestBody* URedisShardRequestBodyLibrary::Make(int32 ShardId, FString MasterHost, FString SlaveHosts, UObject* Outer)
{
	auto Serializable = NewObject<URedisShardRequestBody>(Outer);
	Serializable->ShardId = ShardId;
	Serializable->MasterHost = MasterHost;
	Serializable->SlaveHosts = SlaveHosts;
	
	return Serializable;
}

void URedisShardRequestBodyLibrary::Break(const URedisShardRequestBody* Serializable, int32& ShardId, FString& MasterHost, FString& SlaveHosts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ShardId = Serializable->ShardId;
		MasterHost = Serializable->MasterHost;
		SlaveHosts = Serializable->SlaveHosts;
	}
		
}

