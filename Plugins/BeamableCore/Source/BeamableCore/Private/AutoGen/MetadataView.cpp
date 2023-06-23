
#include "BeamableCore/Public/AutoGen/MetadataView.h"
#include "Serialization/BeamJsonUtils.h"




void UMetadataView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cohorted"), bCohorted);
	Serializer->WriteValue(TEXT("frozen"), bFrozen);
	Serializer->WriteValue(TEXT("partitioned"), bPartitioned);
	Serializer->WriteValue(TEXT("parentLeaderboard"), ParentLeaderboard);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiration"), &Expiration, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);
}

void UMetadataView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cohorted"), bCohorted);
	Serializer->WriteValue(TEXT("frozen"), bFrozen);
	Serializer->WriteValue(TEXT("partitioned"), bPartitioned);
	Serializer->WriteValue(TEXT("parentLeaderboard"), ParentLeaderboard);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("freezeTime"), &FreezeTime, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxEntries"), &MaxEntries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiration"), &Expiration, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("derivatives"), &Derivatives, Serializer);		
}

void UMetadataView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bCohorted = Bag->GetBoolField(TEXT("cohorted"));
	bFrozen = Bag->GetBoolField(TEXT("frozen"));
	bPartitioned = Bag->GetBoolField(TEXT("partitioned"));
	ParentLeaderboard = Bag->GetStringField(TEXT("parentLeaderboard"));
	UBeamJsonUtils::DeserializeOptional<int64>("freezeTime", Bag, FreezeTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<ULeaderboardCohortSettings*>("cohortSettings", Bag, CohortSettings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("permissions", Bag, Permissions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxEntries", Bag, MaxEntries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiration", Bag, Expiration, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("derivatives", Bag, Derivatives, OuterOwner);
}



