
#include "AutoGen/MetadataView.h"
#include "Serialization/BeamJsonUtils.h"


void UMetadataView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);
	Serializer->WriteValue(TEXT("parentLeaderboard"), ParentLeaderboard);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("permissions"), &Permissions, Serializer);
	Serializer->WriteValue(TEXT("frozen"), bFrozen);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	Serializer->WriteValue(TEXT("partitioned"), bPartitioned);
	Serializer->WriteValue(TEXT("cohorted"), bCohorted);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiration"), &Expiration, Serializer);
}

void UMetadataView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);
	Serializer->WriteValue(TEXT("parentLeaderboard"), ParentLeaderboard);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("permissions"), &Permissions, Serializer);
	Serializer->WriteValue(TEXT("frozen"), bFrozen);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	Serializer->WriteValue(TEXT("partitioned"), bPartitioned);
	Serializer->WriteValue(TEXT("cohorted"), bCohorted);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiration"), &Expiration, Serializer);		
}

void UMetadataView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("freezeTime", Bag, FreezeTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("derivatives", Bag, Derivatives, OuterOwner);
	ParentLeaderboard = Bag->GetStringField(TEXT("parentLeaderboard"));
	UBeamJsonUtils::DeserializeOptional<ULeaderboardCohortSettings*>("cohortSettings", Bag, CohortSettings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UClientPermission*>("permissions", Bag, Permissions, OuterOwner);
	bFrozen = Bag->GetBoolField(TEXT("frozen"));
	UBeamJsonUtils::DeserializeOptional<int32>("maxEntries", Bag, MaxEntries, OuterOwner);
	bPartitioned = Bag->GetBoolField(TEXT("partitioned"));
	bCohorted = Bag->GetBoolField(TEXT("cohorted"));
	UBeamJsonUtils::DeserializeOptional<int64>("expiration", Bag, Expiration, OuterOwner);
}