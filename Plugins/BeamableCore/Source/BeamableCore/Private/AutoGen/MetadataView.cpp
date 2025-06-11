
#include "BeamableCore/Public/AutoGen/MetadataView.h"
#include "Serialization/BeamJsonUtils.h"




void UMetadataView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cohorted"), bCohorted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("frozen"), bFrozen, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("partitioned"), bPartitioned, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("parentLeaderboard"), ParentLeaderboard, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiration"), &Expiration, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);
}

void UMetadataView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cohorted"), bCohorted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("frozen"), bFrozen, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("partitioned"), bPartitioned, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("parentLeaderboard"), ParentLeaderboard, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiration"), &Expiration, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);		
}

void UMetadataView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cohorted")), bCohorted);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("frozen")), bFrozen);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("partitioned")), bPartitioned);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("parentLeaderboard")), ParentLeaderboard);
	UBeamJsonUtils::DeserializeOptional<int64>("freezeTime", Bag, FreezeTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<ULeaderboardCohortSettings*>("cohortSettings", Bag, CohortSettings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("permissions", Bag, Permissions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxEntries", Bag, MaxEntries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiration", Bag, Expiration, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("derivatives", Bag, Derivatives, OuterOwner);
}



