
#include "AutoGen/LeaderboardCreateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void ULeaderboardCreateRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scoreName"), &ScoreName, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("partitioned"), &bPartitioned, Serializer);
	Serializer->WriteValue(TEXT("sharded"), bSharded);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("ttl"), &Ttl, Serializer);
}

void ULeaderboardCreateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scoreName"), &ScoreName, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("partitioned"), &bPartitioned, Serializer);
	Serializer->WriteValue(TEXT("sharded"), bSharded);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("ttl"), &Ttl, Serializer);		
}

void ULeaderboardCreateRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("freezeTime", Bag, FreezeTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("derivatives", Bag, Derivatives, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("scoreName", Bag, ScoreName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<ULeaderboardCohortSettings*>("cohortSettings", Bag, CohortSettings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UClientPermission*>("permissions", Bag, Permissions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxEntries", Bag, MaxEntries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("partitioned", Bag, bPartitioned, OuterOwner);
	bSharded = Bag->GetBoolField(TEXT("sharded"));
	UBeamJsonUtils::DeserializeOptional<int64>("ttl", Bag, Ttl, OuterOwner);
}